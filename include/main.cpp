#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>

#include "cleanup.h"
#include "game.h"

const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;

int main()
{
    uint32_t frameStart, frameTime;
    if(Game::instance()->init("game", 100, 100, 640, 480, false))
    {
        while(Game::instance()->running())
        {
            frameStart = SDL_GetTicks();

            Game::instance()->handleEvents();
            Game::instance()->update();
            Game::instance()->render();

            frameTime = SDL_GetTicks() - frameStart;

            if (frameTime < DELAY_TIME)
            {
                SDL_Delay((int)(DELAY_TIME - frameTime));
            }
        }
        Game::instance()->clean();
    }
    else
    {
        std::cout << "Init failed" << std::endl;
    }

    return 0;
}
