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
    velocity_.setX(2);
    acceleration_.setY(0.01);
    SDLGameObject::update();
}

void Player::clean()
{
}
