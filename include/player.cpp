#include "player.h"

Player::Player(const LoaderParams *params)
    : SDLGameObject(params)
{
}

void Player::draw()
{
    SDLGameObject::draw();
}

void Player::update()
{
//    --x_;
    currentFrame_ = int((SDL_GetTicks() / 100) % 6);
}

void Player::clean()
{
}
