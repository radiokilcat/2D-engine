#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <iostream>
#include <SDL2/SDL.h>

#include "loaderparams.h"

class GameObject
{
public:
    GameObject() {};
    virtual void draw() = 0;
    virtual void update() = 0;
    virtual void clean() = 0;

protected:
    GameObject(const LoaderParams* params) {};
    virtual ~GameObject() {};
};
#endif // GAMEOBJECT_H
