#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <iostream>

#include "cleanup.h"
#include "game.h"

void logSDLError(std::ostream &os, const std::string &msg)
{
    os << msg << " error: " << SDL_GetError() << std::endl;
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
}
