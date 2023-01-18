#ifndef GAMEOVER_STATE_H
#define GAMEOVER_STATE_H
#include "GameState.h"
#include "GameObject.h"
#include <vector>

class GameOverState : public GameState {
    public:
        virtual void update();
        virtual void render();

        virtual bool onEnter();
        virtual bool onExit();
        
        virtual std::string getStateID() const { return s_stateID; }
    private:
        static const std::string s_stateID;
        static void s_gameOverToMain();
        static void s_restartPlay();
        std::vector<GameObject*> m_gameObjects;
};

#endif
