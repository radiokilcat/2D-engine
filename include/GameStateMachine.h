#ifndef ISOMETRIC_GAME_GAMESTATEMACHINE_H
#define ISOMETRIC_GAME_GAMESTATEMACHINE_H

#include <vector>
#include "GameState.h"

class GameStateMachine
{
public:
    void pushState(GameState* state);
    void popState();
    void changeState(GameState* state);

    void update();
    void render();
private:
    std::vector<GameState*> states_;
};


#endif //ISOMETRIC_GAME_GAMESTATEMACHINE_H
