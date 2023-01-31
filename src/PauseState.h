#ifndef PAUSE_STATE_H
#define PAUSE_STATE_H
#include "GameObject.h"
#include "MenuState.h"
#include <vector>

class PauseState : public MenuState {
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

    static void s_pauseToMain();
    static void s_resumePlay();
};

#endif
