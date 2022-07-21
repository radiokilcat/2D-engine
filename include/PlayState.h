#ifndef ISOMETRIC_GAME_PLAYSTATE_H
#define ISOMETRIC_GAME_PLAYSTATE_H

#include "GameState.h"

class PlayState : public GameState
{
public:
    bool onEnter() override;
    bool onExit() override;

    void update() override;
    void render() override;

    std::string getID();

private:
    const std::string playID_ = "PLAY";
    std::vector<GameObject*> game_objects_;
};

#endif //ISOMETRIC_GAME_PLAYSTATE_H
