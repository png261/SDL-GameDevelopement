#ifndef GAME_STATE_MACHINE_H
#define GAME_STATE_MACHINE_H

#include "GameState.h"
#include <vector>

class GameStateMachine {
    public:
        void pushState(GameState* pState);
        void changeState(GameState* pState);
        void popState();
        void update();
        void render();
    private:
        GameStateMachine* m_pGameStateMachine;
        std::vector<GameState*> m_gameStates;
};

#endif
