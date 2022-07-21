#include "game.h"
#include "PauseState.h"
#include "MenuButton.h"
#include "inputhandler.h"

#include "PlayState.h"

bool PauseState::onEnter()
{
    if (!TextureManager::instance()->loadTexture("res/main.png",
                                                 "mainbutton", Game::instance()->getRenderer()))
    {
        return false;
    }
    if (!TextureManager::instance()->loadTexture("res/resume.png",
                                                 "resumebutton", Game::instance()->getRenderer()))
    {
        return false;
    }
    /* TODO: place buttons to Window.width / 2 - button.width / 2 */
    GameObject* button1 = new MenuButton(new LoaderParams(220, 100, 200, 100, "mainbutton"), pause_to_main);
    GameObject* button2 = new MenuButton(new LoaderParams(220, 300, 200, 100, "resumebutton"), resume_game);
    game_objects_.push_back(button1);
    game_objects_.push_back(button2);
    std::cout << "Enter Pause state" << std::endl;
    return true;
}

bool PauseState::onExit()
{
    for (const auto& it: game_objects_)
        it->clean();
    game_objects_.clear();
    TextureManager::instance()->clearFromTextureMap("mainbutton");
    TextureManager::instance()->clearFromTextureMap("resumebutton");

    /* TODO: make inputhandler reset() function */
//    InputHandler::instance()->reset();
    return true;
}

void PauseState::update()
{

    for (const auto& it: game_objects_)
        it->update();
}

void PauseState::render()
{
    for (const auto& it: game_objects_)
        it->draw();
}

std::string PauseState::getID()
{
    return id_;
}

void PauseState::pause_to_main()
{
    Game::instance()->getStateMachine()->changeState(new MenuState);
}

void PauseState::resume_game()
{
    Game::instance()->getStateMachine()->popState();
}
