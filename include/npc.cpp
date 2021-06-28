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
    position_.setX(position_.x() + 1);
    currentFrame_ = int((SDL_GetTicks() / 100) % 6);
}

void Npc::clean()
{
}
