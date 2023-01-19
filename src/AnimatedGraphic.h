#ifndef ANIMATED_GRAPHIC_BUTTON_H
#define ANIMATED_GRAPHIC_BUTTON_H

#include "GameObjectFactory.h"
#include "SDLGameObject.h"

class AnimatedGraphic : public SDLGameObject {
    public:
        AnimatedGraphic();
        virtual void load(const LoaderParams* pParams);
        virtual void draw();
        virtual void update();
        virtual void clean();
};

class AnimatedGraphicCreator: public BaseCreator {
    GameObject* createGameObject() const {
        return new AnimatedGraphic();
    }
};



#endif
