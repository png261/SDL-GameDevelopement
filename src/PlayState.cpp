#include "PlayState.h"
#include "Game.h"
#include "GameOverState.h"
#include "GameStateMachine.h"
#include "InputHandler.h"
#include "LevelParser.h"
#include "PauseState.h"
#include "StateParser.h"
#include "TextureManager.h"

const std::string PlayState::s_stateID = "PLAY";

bool PlayState::onEnter() {
    LevelParser levelParser;
    pLevel = levelParser.parseLevel("assets/map.tmx");

    return true;
}

void PlayState::update() {
    /* if(checkCollision(dynamic_cast<SDLGameObject*>(m_gameObjects[0]),
     * dynamic_cast<SDLGameObject*>(m_gameObjects[1]))) { */
    /*     GameStateMachine::Instance()->pushState(new GameOverState()); */
    /* } */
    if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE)) {
        GameStateMachine::Instance()->pushState(new PauseState());
    }
    pLevel->update();
}

void PlayState::render() { pLevel->render(); }

bool PlayState::onExit() {
    for (auto &object : m_gameObjects) {
        object->clean();
    }

    for (auto &texture : m_textureIDList) {
        TextureManager::Instance()->clearFromTextureMap(texture);
    }
    InputHandler::Instance()->reset();
    m_gameObjects.clear();

    return true;
}

bool PlayState::checkCollision(SDLGameObject *p1, SDLGameObject *p2) {

    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA = p1->getPosition().getX();
    rightA = p1->getPosition().getX() + p1->getWidth();
    topA = p1->getPosition().getY();
    bottomA = p1->getPosition().getY() + p1->getHeight();

    // Calculate the sides of rect B
    leftB = p2->getPosition().getX();
    rightB = p2->getPosition().getX() + p2->getWidth();
    topB = p2->getPosition().getY();
    bottomB = p2->getPosition().getY() + p2->getHeight();

    // If any of the sides from A are outside of B
    if (bottomA <= topB) {
        return false;
    }
    if (topA >= bottomB) {
        return false;
    }
    if (rightA <= leftB) {
        return false;
    }
    if (leftA >= rightB) {
        return false;
    }
    return true;
}
