#ifndef PAUSE_STATE_H
#define PAUSE_STATE_H
#include "GameState.h"
#include "GameObject.h"
#include <vector>

class PauseState : public GameState {
    public:
        virtual void update();
        virtual void render();

        virtual bool onEnter();
        virtual bool onExit();
        
        virtual std::string getStateID() const { return s_stateID; }
    private:
        static const std::string s_stateID;
        static void s_pauseToMain();
        static void s_resumePlay();
        std::vector<GameObject*> m_gameObjects;
};

#endif
