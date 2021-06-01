#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SDL2/SDL.h>

#include <iostream>

class GameObject
{
public:
    GameObject();
    void load(int x, int y, int width, int height, std::string texture_id);
    void draw(SDL_Renderer* renderer);;
    void update();;
    void clean();;

protected:
    std::string id_;
    int currentFrame_;
    int currentRow_;
    int x_, y_;
    int width_, height_;
};
#endif // GAMEOBJECT_H
