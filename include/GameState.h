#ifndef ISOMETRIC_GAME_GAMESTATE_H
#define ISOMETRIC_GAME_GAMESTATE_H

#include <string>
#include <vector>

#include "gameobject.h"

class GameState
{
public:
    virtual bool onEnter() = 0;
    virtual bool onExit() = 0;

    virtual void update() = 0;
    virtual void render() = 0;

    virtual std::string getID() = 0;
};

class MenuState : public GameState
{
public:
    bool onEnter() override;
    bool onExit() override;

    void update() override;
    void render() override;

    static void menu_to_play();
    static void exit_from_menu();

    std::string getID();

private:
    const std::string menuID_ = "MENU";
    std::vector<GameObject*> game_objects_;
};


#endif //ISOMETRIC_GAME_GAMESTATE_H
