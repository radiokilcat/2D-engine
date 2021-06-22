#include "sdl_gameobject.h"
#include "texturemanager.h"
#include "game.h"

SDLGameObject::SDLGameObject(const LoaderParams *params)
    :GameObject(params)
{
    x_ = params->getX();
    y_ = params->getY();
    width_ = params->getWidth();
    height_ = params->getHeight();
    id_ = params->getId();
    currentRow_ = 1;
    currentFrame_ = 1;
}

void SDLGameObject::draw()
{
    TextureManager::instance()->drawFrame(id_, x_, y_,
                                          width_, height_,
                                          currentRow_, currentFrame_,
                                          Game::instance()->getRenderer());
}

void SDLGameObject::update()
{

}

void SDLGameObject::clean()
{

}
