#ifndef MENU_BUTTON_H
#define MENU_BUTTON_H

#include "SDLGameObject.h"

class MenuButton : public SDLGameObject {
    public:
        MenuButton (const LoaderParams* pParams);
        virtual void draw();
        virtual void update();
        virtual void clean();
};

enum button_state {
    MOUSE_OUT = 0,
    MOUSE_OVER = 1,
    CLICKED = 2,
};

#endif
