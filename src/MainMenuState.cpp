
#include "MainMenuState.h"
#include "MainMenuState.h"
#include "MenuButton.h"
#include "MenuState.h"
#include "PlayState.h"
#include "StateParser.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "Game.h"
#include "GameStateMachine.h"

const std::string MainMenuState::s_stateID = "MENU";

bool MainMenuState::onEnter() {
    StateParser stateParser;
    if(!stateParser.parseState("test.xml", s_stateID, &m_gameObjects, &m_textureIDList)) {
        return false;
    }

    m_callbacks.push_back(0);
    m_callbacks.push_back(s_menuToPlay);
    m_callbacks.push_back(s_exitFromMenu);

    setCallbacks(m_callbacks);
    return true;
}

void MainMenuState::setCallbacks(const std::vector<Callback> &callbacks) {
    for(auto& object : m_gameObjects) {
        if(dynamic_cast<MenuButton*>(object))
        {
            MenuButton* pButton = dynamic_cast<MenuButton*>(object);
            pButton->setCallback(callbacks[pButton->getCallbackID()]);
        }
    }
}

void MainMenuState::update() {
    for(auto &object : m_gameObjects) {
        object->update();
    }
}

void MainMenuState::render() {
    for(auto &object : m_gameObjects) {
        object->draw();
    }
}

bool MainMenuState::onExit() {
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

void MainMenuState::s_menuToPlay() {
    GameStateMachine::Instance()->changeState(new PlayState());
}

void MainMenuState::s_exitFromMenu() {
    Game::Instance()->quit();
}

