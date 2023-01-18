
#include "PauseState.h"
#include "MenuButton.h"
#include "MenuState.h"
#include "PlayState.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "Game.h"
#include <iostream>

const std::string PauseState::s_stateID = "PAUSE";

bool PauseState::onEnter() {
    std::cout << "entering PauseState" << std::endl;
    if(!TextureManager::Instance()->load("assets/resume.png", "resumebutton", Game::Instance()->getRenderer())) {
        return false;
    }

    if(!TextureManager::Instance()->load("assets/main.png", "mainbutton", Game::Instance()->getRenderer())) {
        return false;
    }
    
    m_gameObjects.push_back(new MenuButton(new LoaderParams(200, 100, 200, 80, "mainbutton"), s_pauseToMain));
    m_gameObjects.push_back(new MenuButton(new LoaderParams(200, 300, 200, 80, "resumebutton"), s_resumePlay));
    return true;
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
        TextureManager::Instance()->clearFromTextureMap(object->getTextureID());
    }
    InputHandler::Instance()->reset();
    m_gameObjects.clear();

    return true;
}

void PauseState::s_pauseToMain() {
    Game::Instance()->getStateMachine()->changeState(new MenuState());
}

void PauseState::s_resumePlay() {
    Game::Instance()->getStateMachine()->popState();
}
