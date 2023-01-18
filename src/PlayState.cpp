#include "PlayState.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "PauseState.h"
#include "Game.h"

const std::string PlayState::s_stateID = "PLAY";

bool PlayState::onEnter() {
    if(!TextureManager::Instance()->load("assets/helicopter.png", "helicopter", Game::Instance()->getRenderer())) {
        return false;
    }

    m_gameObjects.push_back(new Player(new LoaderParams(100, 100, 128, 55, "helicopter")));
    return true;
}


void PlayState::update() {
    if(InputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE))
    {
        Game::Instance()->getStateMachine()->pushState(new PauseState());
    }
    for(auto &object : m_gameObjects) {
        object->update();
    }
}

void PlayState::render() {
    for(auto &object : m_gameObjects) {
        object->draw();
    }
}

bool PlayState::onExit() {
    for(auto &object : m_gameObjects) {
        object->clean();
        TextureManager::Instance()->clearFromTextureMap(object->getTextureID());
    }
    InputHandler::Instance()->reset();
    m_gameObjects.clear();

    return true;
}
