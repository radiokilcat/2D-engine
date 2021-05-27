#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H


class GameObject
{
public:
    GameObject();
    void draw();
    void update();
    void clean();

protected:
    int x_, y_;
};

#endif // GAMEOBJECT_H
