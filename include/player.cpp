#include "player.h"
#include "inputhandler.h"

Player::Player(const LoaderParams *params)
    : SDLGameObject(params)
{
}

void Player::draw_obj()
{
    SDLGameObject::draw();
}

void Player::update()
{
//    --x_;
    velocity_.setX(0);
    velocity_.setY(0);

    handleInput();
    currentFrame_ = int((SDL_GetTicks() / 100) % 6);
    SDLGameObject::update();
}

void Player::clean()
{
}

void Player::handleInput()
{
//    if (InputHandler::instance()->joysticksInitialized())
//    {
//        if (InputHandler::instance()->xvalue(0, 1) > 0 ||
//        InputHandler::instance()->xvalue(0, 1) < 0)
//        {
//            velocity_.setX(1 * InputHandler::instance()->xvalue(0,
//            1));
//        }
//        if (InputHandler::instance()->yvalue(0, 1) > 0 ||
//        InputHandler::instance()->yvalue(0, 1) < 0)
//        {
//            velocity_.setY(1 * InputHandler::instance()->yvalue(0,
//            1));
//        }
//        if (InputHandler::instance()->xvalue(0, 2) > 0 ||
//        InputHandler::instance()->xvalue(0, 2) < 0)
//        {
//            velocity_.setX(1 * InputHandler::instance()->xvalue(0,
//            2));
//        }
//        if (InputHandler::instance()->yvalue(0, 2) > 0 ||
//        InputHandler::instance()->yvalue(0, 2) < 0)
//        {
//            velocity_.setY(1 * InputHandler::instance()->yvalue(0,
//            2));
//        }
//        if (InputHandler::instance()->getButtonState(0, 3))
//        {
//            velocity_.setX(1);
//        }
//    }
//    if (InputHandler::instance()->getMouseButtonState(LEFT))
//    {
//        velocity_.setX(1);
//    }
//    if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_RIGHT))
//    {
//        velocity_.setX(2);
//    }
//    if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_LEFT))
//    {
//        velocity_.setX(-2);
//        currentRow_ = 2;
//    }
//    if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_UP))
//    {
//        velocity_.setY(-2);
//    }
//    if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_DOWN))
//    {
//        velocity_.setY(2);
//    }
    Vector2D* vec = InputHandler::instance()->getMousePosition();
    velocity_ = (*vec - position_) / 50;
}
