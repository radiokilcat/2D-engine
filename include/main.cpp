#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>

#include "cleanup.h"
#include "game.h"

int main()
{
    if(Game::instance()->init("game", 100, 100, 640, 480, false))
    {
        while(Game::instance()->running())
        {
            Game::instance()->handleEvents();
            Game::instance()->update();
            Game::instance()->render();
            SDL_Delay(10);
        }
        Game::instance()->clean();
    }
    else
    {
        std::cout << "Init failed" << std::endl;
    }

    return 0;
}
