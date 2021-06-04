#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SDL2/SDL.h>

#include <iostream>

class GameObject
{
public:
    GameObject();
    virtual void load(int x, int y, int width, int height, std::string texture_id);
    virtual void draw(SDL_Renderer* renderer);;
    virtual void update();;
    virtual void clean();;

protected:
    std::string id_;
    int currentFrame_;
    int currentRow_;
    int x_, y_;
    int width_, height_;
};
#endif // GAMEOBJECT_H
