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

void renderTexture(SDL_Texture* texture, SDL_Renderer* renderer, SDL_Rect dst, SDL_Rect* clip = nullptr)
{
    SDL_RenderCopy(renderer, texture, clip, &dst);
}

void renderTexture(SDL_Texture* texture, SDL_Renderer* renderer, int x, int y, SDL_Rect* clip = nullptr)
{
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    if (clip != nullptr)
    {
        dst.w = clip->w;
        dst.h = clip->h;
    }
    else
    {
        SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);
    }

    renderTexture(texture, renderer, dst, clip);
}

SDL_Texture* renderText(const std::string& message, const std::string& fontFile,
                        SDL_Color color, int fontSize, SDL_Renderer* renderer)
{
    TTF_Font *font = TTF_OpenFont(fontFile.c_str(), fontSize);
        if (font == nullptr){
//            logSDLError(std::cout, "TTF_OpenFont");
            return nullptr;
        }
        //We need to first render to a surface as that's what TTF_RenderText
        //returns, then load that surface into a texture
        SDL_Surface *surf = TTF_RenderText_Blended(font, message.c_str(), color);
        if (surf == nullptr){
            TTF_CloseFont(font);
//            logSDLError(std::cout, "TTF_RenderText");
            return nullptr;
        }
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surf);
        if (texture == nullptr){
//            logSDLError(std::cout, "CreateTexture");
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
    background_ = loadTexture(resPath_ + "background.png", renderer_);
    image_ = loadTexture(resPath_ + "image.png", renderer_);
    if (background_ == nullptr || image_ == nullptr){
        cleanup(background_, image_, renderer_, window_);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    running_ = true;
}

void Game::render()
{
    //First clear the renderer
    SDL_RenderClear(renderer_);

    int iW = 100, iH = 100;
    int x = SCREEN_WIDTH / 2 - iW / 2;
    int y = SCREEN_HEIGHT / 2 - iH / 2;

    SDL_Rect clips[4];
    for ( int i = 0; i < 4; ++i )
    {
        clips[i].x = i / 2 * iW;
        clips[i].y = i % 2 * iH;
        clips[i].w = iW;
        clips[i].h = iH;
    }

    renderTexture(image_, renderer_, x, y, &clips[useClip_]);
    SDL_Color color = { 255, 255, 255, 255 };
    SDL_Texture* text = renderText("Super game", resPath_ + "sample.ttf",
                                    color, 64, renderer_);
    int tW, tH;
    SDL_QueryTexture(text, NULL, NULL, &tW, &tH);
    int tX = SCREEN_WIDTH / 2 - tW / 2;
    int tY = 0;
    renderTexture(text, renderer_, tX, tY);

    SDL_RenderPresent(renderer_);
}

void Game::handleEvents()
{
    SDL_Event e;

    while(SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT)
            running_ = false;
        if (e.type == SDL_KEYDOWN)
            switch (e.key.keysym.sym) {
            case SDLK_1:
                useClip_ = 0;
                break;
            case SDLK_2:
                useClip_ = 1;
                break;
            case SDLK_3:
                useClip_ = 2;
                break;
            case SDLK_4:
                useClip_ = 3;
                break;
            default:
                break;
            }
    }
}

void Game::clean()
{
    cleanup(background_, image_, renderer_, window_);
    IMG_Quit();
    SDL_Quit();
}
