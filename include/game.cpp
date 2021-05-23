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

bool Game::init()
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
        "isometric-test",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        640,
        480,
        0
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

//    texture_manager_.loadTexture(resPath_ + "background.png", "bg", renderer_);
    texture_manager_.loadTexture(resPath_ + "adventurer-Sheet.png", "image", renderer_);

    running_ = true;
}

void Game::render()
{
    //First clear the renderer
    SDL_RenderClear(renderer_);

    int iW = 50, iH = 37;
    int x = SCREEN_WIDTH / 2 - iW / 2;
    int y = SCREEN_HEIGHT / 2 - iH / 2;

//    texture_manager_.draw("bg", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, renderer_ );
    texture_manager_.drawFrame("image", x, y, iW, iH, 2, useClip_, renderer_ );

    SDL_RenderPresent(renderer_);
}

void Game::update()
{
    useClip_ = int((SDL_GetTicks() / 100) % 6);
}

void Game::handleEvents()
{
    SDL_Event e;

    while(SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT)
            running_ = false;
//        if (e.type == SDL_KEYDOWN)
//            switch (e.key.keysym.sym) {
//            case SDLK_1:
//                useClip_ = 0;
//                break;
//            case SDLK_2:
//                useClip_ = 1;
//                break;
//            case SDLK_3:
//                useClip_ = 2;
//                break;
//            case SDLK_4:
//                useClip_ = 3;
//                break;
//            default:
//                break;
//            }
    }
}

void Game::clean()
{
    cleanup(renderer_, window_);
    IMG_Quit();
    SDL_Quit();
}
