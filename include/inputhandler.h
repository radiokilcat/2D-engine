#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_joystick.h>

#include <vector>
#include "vector2d.h"

enum mouse_buttons
{
    LEFT = 0,
    MIDDLE = 1,
    RIGHT = 2
};

class InputHandler
{
public:
    static InputHandler* instance();
    void update();
    void clean();

    void initializeJoysticks();
    bool joysticksInitialized() { return joysticksInitialized_; };

    bool getButtonState(int joy, int buttonNumber);
    bool getMouseButtonState(int buttonNumber);
    Vector2D* getMousePosition() const;

    bool isKeyDown(SDL_Scancode code);

    int xvalue(int joy, int stick);
    int yvalue(int joy, int stick);

private:
    InputHandler();
    ~InputHandler();
    std::vector<SDL_Joystick*> joysticks_;
    std::vector<std::pair<Vector2D*, Vector2D*>> joysticksValues_;
    std::vector<std::vector<bool>> buttonStates_;
    std::vector<bool> mouseButtonStates_;
    Vector2D* mousePosition_;

private:

    const Uint8* keyState_;
    bool joysticksInitialized_;
    const int joystickDeadZone_ = 100000;
};

#endif // INPUTHANDLER_H
