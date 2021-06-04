#ifndef NPC_H
#define NPC_H

#include "gameobject.h"

class Npc : public GameObject
{
public:
    Npc();
    void load(int x, int y, int width, int height, std::string id);
    void draw(SDL_Renderer* renderer);
    void update();
    void clean();
};

#endif // NPC_H
