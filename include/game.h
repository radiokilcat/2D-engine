#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <iostream>

#include "gameobject.h"
#include "player.h"
#include "texturemanager.h"

class Game
{
public:
    Game();
    bool init();
    void render();
    void update();
    void handleEvents();
    void clean();

    SDL_Window *window_;
    SDL_Renderer *renderer_;
    bool running() { return running_; };

private:
    bool running_ = false;
    int useClip_{0};

    SDL_Texture* background_;
    SDL_Texture* image_;
    std::string resPath_;

    const int SCREEN_WIDTH  = 640;
    const int SCREEN_HEIGHT = 480;

    int currentFrame;
    GameObject game_obj_;
    Player player_;
};

#endif // GAME_H
