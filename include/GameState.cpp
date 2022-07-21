#include <iostream>
#include "GameState.h"
#include "texturemanager.h"
#include "game.h"
#include "MenuButton.h"
#include "PlayState.h"

std::string MenuState::getID()
{
    return menuID_;
}

bool MenuState::onEnter()
{
    if (!TextureManager::instance()->loadTexture("res/button.png",
                                                 "playbutton", Game::instance()->getRenderer()))
    {
        return false;
    }
    if (!TextureManager::instance()->loadTexture("res/exit.png",
                                                 "exitbutton", Game::instance()->getRenderer()))
    {
        return false;
    }
    GameObject* button1 = new MenuButton(new LoaderParams(100, 100, 400, 100, "playbutton"), menu_to_play);
    GameObject* button2 = new MenuButton(new LoaderParams(100, 300, 400, 100, "exitbutton"), exit_from_menu);
    game_objects_.push_back(button1);
    game_objects_.push_back(button2);
    std::cout << "Enter Menu state" << std::endl;
    return true;
}

void MenuState::render()
{
    for (auto it: game_objects_)
    {
        it->draw();
    }
}

bool MenuState::onExit()
{
    for (auto it: game_objects_)
    {
        it->clean();
    }
    game_objects_.clear();
    TextureManager::instance()->clearFromTextureMap("playbutton");
    TextureManager::instance()->clearFromTextureMap("exitbutton");
    std::cout << "Exit Menu state" << std::endl;
    return true;
}

void MenuState::update()
{
    for (auto it: game_objects_)
    {
        it->update();
    }
}

void MenuState::menu_to_play()
{
    std::cout << "play button clicked" << std::endl;
    Game::instance()->getStateMachine()->changeState(new PlayState);
}

void MenuState::exit_from_menu()
{
    std::cout << "exit button clicked" << std::endl;
    Game::instance()->quit();
}

