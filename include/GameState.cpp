#include "GameState.h"

std::string MenuState::getID()
{
    return menuID_;
}

bool MenuState::onEnter()
{
}

void MenuState::render()
{
}

bool MenuState::onExit()
{
}

void MenuState::update()
{
}

std::string PlayState::getID()
{
    return playID_;
}

bool PlayState::onEnter()
{
}

bool PlayState::onExit()
{
}

void PlayState::update()
{
}

void PlayState::render()
{
}
