#include "Player.h"
#include "GameObject.h"
#include "InputHandler.h"

Player::Player(const LoaderParams* pParams) : SDLGameObject(pParams) {

}

void Player::draw() {
    SDLGameObject::draw();
}

void Player::update() {
    m_currentFrame = int(((SDL_GetTicks() / 100) % 6));

    if(InputHandler::Instance()->isKeyDown(SDL_SCANCODE_D)) {
        m_velocity.setX(0.01);
    };

    if(InputHandler::Instance()->isKeyDown(SDL_SCANCODE_A)) {
        m_velocity.setX(-0.01);
    };
    SDLGameObject::update();
}

void Player::clean(){
}
