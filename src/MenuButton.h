#ifndef MENU_BUTTON_H
#define MENU_BUTTON_H

#include "GameObjectFactory.h"
#include "SDLGameObject.h"

class MenuButton : public SDLGameObject {
  public:
    MenuButton();
    virtual void draw();
    virtual void update();
    virtual void clean();
    virtual void load(const LoaderParams *pParams);
    void setCallback(void (*callback)()) { m_callback = callback; }
    int getCallbackID() { return m_callbackID; }

  private:
    bool m_bReleased;
    int m_callbackID;
    void (*m_callback)();
};

enum button_state {
    MOUSE_OUT = 0,
    MOUSE_OVER = 1,
    CLICKED = 2,
};

#endif
