#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <iostream>

#include "res_path.h"
#include "cleanup.h"
#include "game.h"

void logSDLError(std::ostream &os, const std::string &msg)
{
    os << msg << " error: " << SDL_GetError() << std::endl;
}

SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *renderer)
{
    SDL_Texture* texture = IMG_LoadTexture(renderer, file.c_str());
    if (texture == nullptr)
        logSDLError(std::cout, "CreateTextureFromSurface");
    return texture;
}

SDL_Texture* renderText(const std::string& message, const std::string& fontFile,
                        SDL_Color color, int fontSize, SDL_Renderer* renderer)
{
    TTF_Font *font = TTF_OpenFont(fontFile.c_str(), fontSize);
        if (font == nullptr){
            logSDLError(std::cout, "TTF_OpenFont");
            return nullptr;
        }
        //We need to first render to a surface as that's what TTF_RenderText
        //returns, then load that surface into a texture
        SDL_Surface *surf = TTF_RenderText_Blended(font, message.c_str(), color);
        if (surf == nullptr){
            TTF_CloseFont(font);
            logSDLError(std::cout, "TTF_RenderText");
            return nullptr;
        }
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surf);
        if (texture == nullptr){
            logSDLError(std::cout, "CreateTexture");
        }
        //Clean up the surface and font
        SDL_FreeSurface(surf);
        TTF_CloseFont(font);
        return texture;
}

Game::Game()
{

}

Game* Game::instance_ = 0;
Game* Game::instance()
{
    if (instance_ == 0)
    {
        instance_ = new Game();
        return instance_;
    }
    else {
        return instance_;
    }
}

bool Game::init(const char* title, int xPos, int yPos,
                int width, int height, bool fullscreen )
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        logSDLError(std::cout, "SDL_Init");
        return 1;
    }

    if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
    {
        logSDLError(std::cout, "IMG_Init");
        SDL_Quit();
        return 1;
    }

    if (TTF_Init() != 0)
    {
        logSDLError(std::cout, "TTF_Init");
        SDL_Quit();
        return 1;
    }

    window_ = SDL_CreateWindow(
        title,
        xPos,
        yPos,
        width,
        height,
        fullscreen
    );

    if (window_ == nullptr){
        logSDLError(std::cout, "CreateWindow");
        SDL_Quit();
        return 1;
    }

    renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_SOFTWARE);
    if (renderer_ == nullptr){
        logSDLError(std::cout, "CreateRenderer");
        cleanup(window_);
        SDL_Quit();
        return 1;
    }
    resPath_ = getResourcePath("");

    TextureManager::instance()->loadTexture(resPath_ + "adventurer-Sheet.png", "image", renderer_);

    game_objects_.push_back(new Player(new LoaderParams(100, 100, 50, 37, "image")));
    game_objects_.push_back(new Npc(new LoaderParams(300, 300, 50, 37, "image")));

    running_ = true;
}

void Game::render()
{
    SDL_RenderClear(renderer_);

    for (auto it : game_objects_)
        it->draw();

    SDL_RenderPresent(renderer_);
}

void Game::update()
{
    useClip_ = int((SDL_GetTicks() / 100) % 6);
    for (auto it : game_objects_)
        it->update();
}

void Game::handleEvents()
{
    SDL_Event e;

    while(SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT)
            running_ = false;
    }
}

void Game::clean()
{
    cleanup(renderer_, window_);
    IMG_Quit();
    SDL_Quit();
}
