#ifndef OBJECT_LAYER_H
#define OBJECT_LAYER_H

#include "GameObject.h"
#include "Layer.h"

#include <vector>

class ObjectLayer : public Layer {
  public:
    virtual void update();
    virtual void render();
    std::vector<GameObject *> *getGameObjects() { return &m_gameObjects; }

  private:
    std::vector<GameObject *> m_gameObjects;
};

#endif
