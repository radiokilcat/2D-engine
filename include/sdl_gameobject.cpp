#include "sdl_gameobject.h"
#include "texturemanager.h"
#include "game.h"

SDLGameObject::SDLGameObject(const LoaderParams *params)
    :GameObject(params)
    , position_(params->getX(), params->getY())
    , velocity_(0,0)
    , acceleration_(0,0)
{
    width_ = params->getWidth();
    height_ = params->getHeight();
    id_ = params->getId();
    currentRow_ = 1;
    currentFrame_ = 1;
}

void SDLGameObject::draw()
{
    if (velocity_.x() < 0)
    {
        TextureManager::instance()->drawFrame(id_, (Uint32)position_.x(), (Uint32)position_.y(),
                                              width_, height_,
                                              currentRow_, currentFrame_,
                                              Game::instance()->getRenderer(), SDL_FLIP_HORIZONTAL);
    }
    else
    {
        TextureManager::instance()->drawFrame(id_, (Uint32)position_.x(), (Uint32)position_.y(),
                                              width_, height_,
                                              currentRow_, currentFrame_,
                                              Game::instance()->getRenderer());
    }
}

void SDLGameObject::update()
{
    velocity_ += acceleration_;
    position_ += velocity_;
}

void SDLGameObject::clean()
{

}
