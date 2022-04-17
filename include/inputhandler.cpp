#include <iostream>
#include "inputhandler.h"

#include "game.h"


void InputHandler::initializeJoysticks()
{
    if (SDL_WasInit(SDL_INIT_JOYSTICK) == 0)
    {
        SDL_InitSubSystem(SDL_INIT_JOYSTICK);
    }

    if (SDL_NumJoysticks() > 0)
    {
        for (int i = 0; i < SDL_NumJoysticks(); ++i)
        {
            SDL_Joystick* joy = SDL_JoystickOpen(i);

            if (joy)
            {
                joysticks_.push_back(joy);
                joysticksValues_.push_back(std::make_pair(new Vector2D(0,0), new Vector2D(0,0)));
                std::vector<bool> tempButtons;
                for (int j = 0; j < SDL_JoystickNumButtons(joy); ++j)
                {
                    tempButtons.push_back(false);
                }
                buttonStates_.push_back(tempButtons);
            }
            else
            {
                std::cout << SDL_GetError();
            }
        }
        SDL_JoystickEventState(SDL_ENABLE);
        joysticksInitialized_ = true;

        std::cout << "Initialized " << joysticks_.size() << " joystics";
    }
    else
    {
        joysticksInitialized_ = false;
    }
}

bool InputHandler::getButtonState(int joy, int buttonNumber)
{
    return buttonStates_[joy][buttonNumber];
}

bool InputHandler::getMouseButtonState(int buttonNumber)
{
    return mouseButtonStates_[buttonNumber];
}

bool InputHandler::isKeyDown(SDL_Scancode key)
{
    if (keyState_ != 0)
    {
        if (keyState_[key] == 1)
            return true;
        else
            return false;
    }
    return false;
}

int InputHandler::xvalue(int joy, int stick)
{
    if (joysticksValues_.size() > 0)
    {
        if (stick == 1)
            return joysticksValues_[joy].first->x();
        else if (stick == 2)
            return joysticksValues_[joy].second->x();
    }
    return 0;
}

int InputHandler::yvalue(int joy, int stick)
{
    if (joysticksValues_.size() > 0)
    {
        if (stick == 1)
            return joysticksValues_[joy].first->y();
        else if (stick == 2)
            return joysticksValues_[joy].second->y();
    }
    return 0;
}

static InputHandler* instance_;
InputHandler *InputHandler::instance()
{
    if (instance_ == 0)
    {
        instance_ = new InputHandler();
    }
    return instance_;
}

void InputHandler::update()
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        keyState_ = SDL_GetKeyboardState(0);
        if (event.type == SDL_QUIT)
        {
            Game::instance()->quit();
        }
        if (event.type == SDL_JOYAXISMOTION)
        {
            int which_joystick = event.jaxis.which;
            if (event.jaxis.axis == 0)  //left stick to move left && right
            {
                if (event.jaxis.value > joystickDeadZone_)
                    joysticksValues_[which_joystick].first->setX(1);
                else if(event.jaxis.value < -joystickDeadZone_)
                    joysticksValues_[which_joystick].first->setX(-1);
                else
                    joysticksValues_[which_joystick].first->setX(0);
            }
            if (event.jaxis.axis == 1) // left stick move up && down
            {
                if (event.jaxis.value > joystickDeadZone_)
                    joysticksValues_[which_joystick].first->setY(1);
                else if(event.jaxis.value < -joystickDeadZone_)
                    joysticksValues_[which_joystick].first->setY(-1);
                else
                    joysticksValues_[which_joystick].first->setY(0);

            }
            if (event.jaxis.axis == 3) // right stick move left && right
            {
                if (event.jaxis.value > joystickDeadZone_)
                    joysticksValues_[which_joystick].second->setX(1);
                else if(event.jaxis.value < -joystickDeadZone_)
                    joysticksValues_[which_joystick].second->setX(-1);
                else
                    joysticksValues_[which_joystick].second->setX(0);

            }
            if (event.jaxis.axis == 4) // right stick move up && down
            {
                if (event.jaxis.value > joystickDeadZone_)
                    joysticksValues_[which_joystick].second->setY(1);
                else if(event.jaxis.value < -joystickDeadZone_)
                    joysticksValues_[which_joystick].second->setY(-1);
                else
                    joysticksValues_[which_joystick].second->setY(0);
            }
        }
        if (event.type == SDL_JOYBUTTONDOWN)
        {
            int whichOne = event.jaxis.which;
            buttonStates_[whichOne][event.jbutton.button] = true;
        }
        if (event.type == SDL_JOYBUTTONUP)
        {
            int whichOne = event.jaxis.which;
            buttonStates_[whichOne][event.jbutton.button] = false;
        }
        if (event.button.type == SDL_MOUSEBUTTONDOWN)
        {
            if (event.button.button == SDL_BUTTON_LEFT)
                mouseButtonStates_[LEFT] = true;
            if (event.button.button == SDL_BUTTON_MIDDLE)
                mouseButtonStates_[MIDDLE] = true;
            if (event.button.button == SDL_BUTTON_RIGHT)
                mouseButtonStates_[RIGHT] = true;
        }
        if (event.button.type == SDL_MOUSEBUTTONUP)
        {
            if (event.button.button == SDL_BUTTON_LEFT)
                mouseButtonStates_[LEFT] = false;
            if (event.button.button == SDL_BUTTON_MIDDLE)
                mouseButtonStates_[MIDDLE] = false;
            if (event.button.button == SDL_BUTTON_RIGHT)
                mouseButtonStates_[RIGHT] = false;
        }
        if (event.type = SDL_MOUSEMOTION)
        {
            mousePosition_->setX(event.motion.x);
            mousePosition_->setY(event.motion.y);
        }
    }

}

void InputHandler::clean()
{
    if (joysticksInitialized_)
    {
        for (uint i = 0; i < SDL_NumJoysticks(); ++i)
        {
            SDL_JoystickClose(joysticks_[i]);
        }
    }
}

InputHandler::InputHandler()
: mousePosition_{new Vector2D{0.0, 0.0}}
{
    for (int i = 0; i < 3; ++i)
    {
        mouseButtonStates_.push_back(false);
    }
}

Vector2D* InputHandler::getMousePosition() const
{
    return mousePosition_;
}
