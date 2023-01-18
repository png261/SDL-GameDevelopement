#include "MenuState.h"
#include "MenuButton.h"
#include "PlayState.h"
#include "InputHandler.h"
#include "TextureManager.h"
#include "Game.h"
#include <iostream>

const std::string MenuState::s_stateID = "MENU";

bool MenuState::onEnter() {
    std::cout << "entering menustate" << std::endl;
    if(!TextureManager::Instance()->load("assets/button.png", "playbutton", Game::Instance()->getRenderer())) {
        return false;
    }

    if(!TextureManager::Instance()->load("assets/exit.png", "exitbutton", Game::Instance()->getRenderer())) {
        return false;
    }
    
    m_gameObjects.push_back(new MenuButton(new LoaderParams(100, 100, 400, 100, "playbutton"), s_menuToPlay));
    m_gameObjects.push_back(new MenuButton(new LoaderParams(100, 300, 400, 100, "exitbutton"), s_exitFromMenu));
    return true;
}

void MenuState::update() {
    for(auto &object : m_gameObjects) {
        object->update();
    }
}

void MenuState::render() {
    for(auto &object : m_gameObjects) {
        object->draw();
    }
}

bool MenuState::onExit() {
    for(auto &object : m_gameObjects) {
        object->clean();
        TextureManager::Instance()->clearFromTextureMap(object->getTextureID());
    }
    InputHandler::Instance()->reset();
    m_gameObjects.clear();

    return true;
}

void MenuState::s_menuToPlay() {
    Game::Instance()->getStateMachine()->changeState(new PlayState());
}

void MenuState::s_exitFromMenu() {
    Game::Instance()->quit();
}
