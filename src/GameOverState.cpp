#include "GameOverState.h"
#include "MainMenuState.h"
#include "MenuButton.h"
#include "MenuState.h"
#include "PlayState.h"
#include "StateParser.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "Game.h"
#include "GameStateMachine.h"

const std::string GameOverState::s_stateID = "GAMEOVER";

bool GameOverState::onEnter() {
    StateParser stateParser;
    if(!stateParser.parseState("test.xml", s_stateID, &m_gameObjects, &m_textureIDList)) {
        return false;
    }

    m_callbacks.push_back(0);
    m_callbacks.push_back(s_gameOverToMain);
    m_callbacks.push_back(s_restartPlay);

    setCallbacks(m_callbacks);
    return true;
}

void GameOverState::setCallbacks(const std::vector<Callback> &callbacks) {
    for(auto& object : m_gameObjects) {
        if(dynamic_cast<MenuButton*>(object))
        {
            MenuButton* pButton = dynamic_cast<MenuButton*>(object);
            pButton->setCallback(callbacks[pButton->getCallbackID()]);
        }
    }
}

void GameOverState::update() {
    for(auto &object : m_gameObjects) {
        object->update();
    }
}

void GameOverState::render() {
    for(auto &object : m_gameObjects) {
        object->draw();
    }
}

bool GameOverState::onExit() {
    for(auto &object : m_gameObjects) {
        object->clean();
    }
    m_gameObjects.clear();

    for(auto& texture : m_textureIDList) {
        TextureManager::Instance()->clearFromTextureMap(texture);
    }

    InputHandler::Instance()->reset();

    return true;
}

void GameOverState::s_gameOverToMain() {
    GameStateMachine::Instance()->changeState(new MainMenuState());
}

void GameOverState::s_restartPlay() {
    GameStateMachine::Instance()->changeState(new PlayState());
}

