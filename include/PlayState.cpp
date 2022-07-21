#include "PlayState.h"
#include "texturemanager.h"
#include "res_path.h"
#include "player.h"
#include "game.h"
#include "inputhandler.h"
#include "PauseState.h"

std::string PlayState::getID()
{
    return playID_;
}

bool PlayState::onEnter()
{
    std::cout << "Enter Play state" << std::endl;
    std::string resPath_ = getResourcePath("");
    if(!TextureManager::instance()->loadTexture(resPath_ + "adventurer-Sheet.png", "image",
                                                Game::instance()->getRenderer()))
    {
        return false;
    }
    game_objects_.push_back(new Player(new LoaderParams(100, 100, 50, 37, "image")));
    return true;
}

bool PlayState::onExit()
{
    for (const auto& it: game_objects_)
        it->clean();
    game_objects_.clear();
    TextureManager::instance()->clearFromTextureMap("image");
    std::cout << "Exit Play state" << std::endl;
    return true;
}

void PlayState::update()
{
    if (InputHandler::instance()->isKeyDown(SDL_SCANCODE_ESCAPE))
        Game::instance()->getStateMachine()->pushState(new PauseState);

    for (const auto& it: game_objects_)
        it->update();
}

void PlayState::render()
{
    for (const auto& it: game_objects_)
        it->draw();
}
