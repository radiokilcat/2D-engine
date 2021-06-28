#ifndef SDLGAMEOBJECT_H
#define SDLGAMEOBJECT_H

#include "gameobject.h"
#include "loaderparams.h"
#include "vector2d.h"

class SDLGameObject : public GameObject
{
public:
    SDLGameObject(const LoaderParams* params);

    virtual void draw() override;
    virtual void update() override;
    virtual void clean() override;

protected:
    std::string id_;
    int currentFrame_;
    int currentRow_;
    Vector2D position_;
    Vector2D velocity_;
    Vector2D acceleration_;
    int width_, height_;
};

#endif // SDLGAMEOBJECT_H
