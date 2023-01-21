#include "PauseState.h"
#include "MainMenuState.h"
#include "MenuButton.h"
#include "MenuState.h"
#include "PlayState.h"
#include "StateParser.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "Game.h"
#include "GameStateMachine.h"
#include <iostream>

const std::string PauseState::s_stateID = "PAUSE";

bool PauseState::onEnter() {
    StateParser stateParser;
    if(!stateParser.parseState("test.xml", s_stateID, &m_gameObjects, &m_textureIDList)) {
        return false;
    }

    m_callbacks.push_back(0);
    m_callbacks.push_back(s_pauseToMain);
    m_callbacks.push_back(s_resumePlay);

    setCallbacks(m_callbacks);
    return true;
}

void PauseState::setCallbacks(const std::vector<Callback> &callbacks) {
    for(auto& object : m_gameObjects) {
        if(dynamic_cast<MenuButton*>(object))
        {
            MenuButton* pButton = dynamic_cast<MenuButton*>(object);
            pButton->setCallback(callbacks[pButton->getCallbackID()]);
        }
    }
}

void PauseState::update() {
    for(auto &object : m_gameObjects) {
        object->update();
    }
}

void PauseState::render() {
    for(auto &object : m_gameObjects) {
        object->draw();
    }
}

bool PauseState::onExit() {
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

void PauseState::s_pauseToMain() {
    GameStateMachine::Instance()->changeState(new MainMenuState());
}

void PauseState::s_resumePlay() {
    GameStateMachine::Instance()->popState();
}
