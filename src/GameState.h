#ifndef GAME_STATE_H
#define GAME_STATE_H
#include <string>
#include <vector>

#include "GameObject.h"

class GameState {
  public:
    virtual void update() = 0;
    virtual void render() = 0;

    virtual bool onEnter() = 0;
    virtual bool onExit() = 0;

    virtual std::string getStateID() const = 0;

  protected:
    std::vector<std::string> m_textureIDList;
};

#endif
