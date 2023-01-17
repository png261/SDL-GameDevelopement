#include "Enemy.h"
#include "GameObject.h"

Enemy::Enemy(const LoaderParams* pParams) : SDLGameObject(pParams) {

}

void Enemy::draw() {
    SDLGameObject::draw();
}

void Enemy::update() {
    m_currentFrame = int(((SDL_GetTicks() / 100) % 6));

    SDLGameObject::update();
}

void Enemy::clean(){
}

