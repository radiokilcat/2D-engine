#ifndef NPC_H
#define NPC_H

#include "gameobject.h"
#include "sdl_gameobject.h"

class Npc : public SDLGameObject
{
public:
    Npc(const LoaderParams* params);
    void draw_obj();
    void update();
    void clean();
};

#endif // NPC_H
