#include "npc.h"
#include "loaderparams.h"

Npc::Npc(const LoaderParams *params)
    : SDLGameObject(params)
{
}

void Npc::draw()
{
    SDLGameObject::draw();
}

void Npc::update()
{
//    ++x_;
//    ++y_;
    currentFrame_ = int((SDL_GetTicks() / 100) % 6);
}

void Npc::clean()
{
}
