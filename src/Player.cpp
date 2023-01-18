#include "Player.h"
#include "Game.h"
#include "GameObject.h"
#include "InputHandler.h"
#include "PauseState.h"

Player::Player(const LoaderParams* pParams) : SDLGameObject(pParams) {

}

void Player::draw() {
    SDLGameObject::draw();
}

void Player::update() {
    handleInput();
    SDLGameObject::update();
}

void Player::handleInput() {
    Vector2D* target = InputHandler::Instance() ->getMousePosition();
    m_velocity = *target - m_position;
    m_velocity /= 10000;
}

void Player::clean(){
    SDLGameObject::clean();
}
