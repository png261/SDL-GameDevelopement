#ifndef MAIN_MENU_STATE_H
#define MAIN_MENU_STATE_H

#include "GameObject.h"
#include "MenuState.h"
#include <vector>

class MainMenuState : public MenuState {
  public:
    virtual void update();
    virtual void render();

    virtual bool onEnter();
    virtual bool onExit();

    virtual std::string getStateID() const { return s_stateID; }

  private:
    static const std::string s_stateID;
    std::vector<GameObject *> m_gameObjects;
    virtual void setCallbacks(const std::vector<Callback> &callbacks);

    static void s_menuToPlay();
    static void s_exitFromMenu();
};

#endif
