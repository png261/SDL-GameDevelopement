#include "Player.h"
#include "Game.h"
#include "GameObject.h"
#include "InputHandler.h"
#include "PauseState.h"
#include <iostream>

Player::Player() : SDLGameObject() {}

void Player::load(const LoaderParams *pParams) { SDLGameObject::load(pParams); }

void Player::draw() { SDLGameObject::draw(); }

void Player::update() {
    handleInput();
    SDLGameObject::update();
}

void Player::handleInput() {
    Vector2D *target = InputHandler::Instance()->getMousePosition();

    m_velocity = *target - m_position;
    m_velocity /= 100;
}

void Player::clean() { SDLGameObject::clean(); }
