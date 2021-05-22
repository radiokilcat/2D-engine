#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <iostream>


class Game
{
public:
    Game();
    bool init();
    SDL_Window *window_;
    SDL_Renderer *renderer_;
};

#endif // GAME_H
