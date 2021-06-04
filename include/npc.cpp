#include "npc.h"

Npc::Npc()
{

}

void Npc::load(int x, int y, int width, int height, std::string texture_id)
{
    GameObject::load(x, y, width, height, texture_id);
}

void Npc::draw(SDL_Renderer* renderer)
{
    GameObject::draw(renderer);
}

void Npc::update()
{
    ++x_;
    ++y_;
    currentFrame_ = int((SDL_GetTicks() / 100) % 6);
}

void Npc::clean()
{
    GameObject::clean();
}
