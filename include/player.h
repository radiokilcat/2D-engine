#ifndef PLAYER_H
#define PLAYER_H

#include "gameobject.h"

class Player: public GameObject
{
public:
    Player();
    void load(int x, int y, int width, int height, std::string texture_id);
    void draw(SDL_Renderer* renderer);
    void update();
    void clean();
private:
};

#endif // PLAYER_H
