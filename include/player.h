#ifndef PLAYER_H
#define PLAYER_H

#include "gameobject.h"
#include "sdl_gameobject.h"
#include "loaderparams.h"

class Player: public SDLGameObject
{
public:
    Player(const LoaderParams* params);
    void draw_obj();
    void update();
    void clean();
    void handleInput();
private:
};

#endif // PLAYER_H
