#include "gameobject.h"

#include "texturemanager.h"

GameObject::GameObject()
{
}

void GameObject::load(int x, int y, int width, int height, std::string texture_id)
{
    x_ = x;
    y_ = y;
    width_ = width;
    height_ = height;
    id_ = texture_id;

    currentRow_ = 1;
    currentFrame_ = 1;
}


void GameObject::draw(SDL_Renderer *renderer)
{
    TextureManager::instance()->drawFrame(id_, x_, y_,
                                          width_, height_,
                                          currentRow_, currentFrame_, renderer);
    std::cout << "game object draw" << std::endl;
}

void GameObject::update()
{
    if (x_ < 500)
        ++x_;
    std::cout << "game object update" << std::endl;
}

void GameObject::clean()
{
    std::cout << "game object clean" << std::endl;
}
