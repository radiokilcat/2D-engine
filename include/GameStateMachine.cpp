#include "GameStateMachine.h"


void GameStateMachine::pushState(GameState* state)
{
    states_.push_back(state);
    state->onEnter();
}

void GameStateMachine::popState()
{
    if (!states_.empty())
    {
        if(states_.back()->onExit())
        {
            delete states_.back();
            states_.pop_back();
        }
    }

}

void GameStateMachine::changeState(GameState* state)
{
    if (!states_.empty())
    {
        if (states_.back()->getID() == state->getID())
            return;

        if(states_.back()->onExit())
        {
            delete states_.back();
            states_.pop_back();
        }
    }
    states_.push_back(state);
    state->onEnter();
}
