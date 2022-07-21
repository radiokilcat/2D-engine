#ifndef ISOMETRIC_GAME_PAUSESTATE_H
#define ISOMETRIC_GAME_PAUSESTATE_H

#include "GameState.h"

class PauseState : public GameState
{
public:
    bool onEnter() override;
    bool onExit() override;

    void update() override;
    void render() override;

    std::string getID() override;

    static void pause_to_main();
    static void resume_game();
private:
    std::vector<GameObject*> game_objects_;
    std::string id_ = "PAUSE";
};


#endif //ISOMETRIC_GAME_PAUSESTATE_H
