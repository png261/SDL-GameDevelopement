#ifndef PLAYER_H
#define PLAYER_H

#include "SDLGameObject.h"

class Player : public SDLGameObject {
  public:
    virtual void load(const LoaderParams *pParams);
    virtual void draw();
    virtual void update();
    virtual void clean();
    virtual void handleInput();
    Player();
};

#endif
