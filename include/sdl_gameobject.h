#ifndef SDLGAMEOBJECT_H
#define SDLGAMEOBJECT_H

#include "gameobject.h"
#include "loaderparams.h"

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
    int x_, y_;
    int width_, height_;
};

#endif // SDLGAMEOBJECT_H
