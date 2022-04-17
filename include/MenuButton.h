#ifndef ISOMETRIC_GAME_MENUBUTTON_H
#define ISOMETRIC_GAME_MENUBUTTON_H

#include "sdl_gameobject.h"

class MenuButton : public SDLGameObject
{
public:
    MenuButton(const LoaderParams* params, void (*callback)());

    virtual void draw();
    virtual void update();
    virtual void clean();

private:

    enum button_states
    {
        MOUSE_OUT = 0,
        MOUSE_OVER = 1,
        CLICKED = 2
    };

    void (*callback_)();
    bool released_;

};


#endif //ISOMETRIC_GAME_MENUBUTTON_H
