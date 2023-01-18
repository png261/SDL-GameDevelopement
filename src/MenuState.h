#ifndef MENU_STATE_H
#define MENU_STATE_H
#include "GameState.h"
#include "GameObject.h"
#include <vector>

class MenuState : public GameState {
    public:
        virtual void update();
        virtual void render();

        virtual bool onEnter();
        virtual bool onExit();
        
        virtual std::string getStateID() const { return s_menuID; }
    private:
        static const std::string s_menuID;
        static void s_menuToPlay();
        static void s_exitFromMenu();
        std::vector<GameObject*> m_gameObjects;
};

#endif
