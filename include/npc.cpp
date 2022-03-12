#include "npc.h"
#include "loaderparams.h"

Npc::Npc(const LoaderParams *params)
    : SDLGameObject(params)
{
}

void Npc::draw_obj()
{
    SDLGameObject::draw();
}

void Npc::update()
{
//    ++x_;.
//    ++y_;
//    if (position_.x() >= 400)

//        position_.setX(position_.x() - 1);
//    else if (position_.x() < 300)
//        position_.setX(position_.x() + 1);

    currentFrame_ = int((SDL_GetTicks() / 100) % 6);
}

void Npc::clean()
{
}
