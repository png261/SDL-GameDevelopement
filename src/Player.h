#ifndef PLAYER_H
#define PLAYER_H
#include "GameObject.h"

class Player : public GameObject {
    public:
        virtual void load(int x, int y, int width, int height, std::string textureID);
        virtual void draw(SDL_Renderer* pRenderer);
        virtual void update();
        virtual void clean();
};

#endif
