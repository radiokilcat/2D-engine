#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>

#include "cleanup.h"
#include "game.h"

int main()
{
    Game game;
    game.init();

    while(game.running())
    {
        game.handleEvents();
        game.update();
        game.render();
        SDL_Delay(10);
    }
    game.clean();

    return 0;
}
