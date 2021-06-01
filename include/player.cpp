#include "player.h"

Player::Player()
{

}

void Player::load(int x, int y, int width, int height, std::string texture_id)
{
    GameObject::load(x, y, width, height, texture_id);
}

void Player::draw(SDL_Renderer* renderer)
{
    GameObject::draw(renderer);
}

void Player::update()
{
    --x_;
}

void Player::clean()
{
    GameObject::clean();
}
