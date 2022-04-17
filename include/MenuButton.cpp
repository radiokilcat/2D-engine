#include "inputhandler.h"
#include "MenuButton.h"

MenuButton::MenuButton(const LoaderParams *params, void (*callback)())
  : SDLGameObject(params),
    callback_(callback)
{
    currentFrame_ = MOUSE_OUT;
}

void MenuButton::draw()
{
    SDLGameObject::draw();
}

void MenuButton::update()
{
    Vector2D* MousePos = InputHandler::instance()->getMousePosition();
    if(MousePos->x() < (position_.x() + width_)
    && MousePos->x() > position_.x()
    && MousePos->y() < (position_.y() + height_)
    && MousePos->y() > position_.y())
    {
        if (InputHandler::instance()->getMouseButtonState(LEFT) && released_)
        {
            currentFrame_ = CLICKED;
            callback_();
            released_ = false;
        }
        else if (!InputHandler::instance()->getMouseButtonState(LEFT))
        {
            released_ = true;
            currentFrame_ = MOUSE_OVER;
        }
    }
    else
    {
        currentFrame_ = MOUSE_OUT;
    }
}

void MenuButton::clean()
{
    SDLGameObject::clean();
}
