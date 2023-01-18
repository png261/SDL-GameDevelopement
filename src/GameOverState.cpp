#include "GameOverState.h"
#include "AnimatedGraphic.h"
#include "MenuButton.h"
#include "MenuState.h"
#include "PlayState.h"
#include "InputHandler.h"
#include "TextureManager.h"
#include "Game.h"
#include <iostream>

const std::string GameOverState::s_stateID = "GAMEOVER";

bool GameOverState::onEnter() {
    SDL_Log("Game OVer");
    if(!TextureManager::Instance()->load("assets/gameover.png",
                "gameovertext", Game::Instance()->getRenderer()))
    {
        return false;
    }
    if(!TextureManager::Instance()->load("assets/main.png",
                "mainbutton", Game::Instance()->getRenderer()))
    {
        return false;
    }
    if(!TextureManager::Instance()->load("assets/restart.png",
                "restartbutton", Game::Instance()->getRenderer()))
    {
        return false;
    }
    
    GameObject* gameOverText = new AnimatedGraphic(new LoaderParams(200, 100, 190, 30, "gameovertext", 2), 2);
    GameObject* button1 = new MenuButton(new LoaderParams(200, 200, 200, 80, "mainbutton"), s_gameOverToMain);
    GameObject* button2 = new MenuButton(new LoaderParams(200, 300, 200, 80, "restartbutton"), s_restartPlay);

    m_gameObjects.push_back(gameOverText);
    m_gameObjects.push_back(button1);
    m_gameObjects.push_back(button2);
    return true;
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
        TextureManager::Instance()->clearFromTextureMap(object->getTextureID());
    }
    InputHandler::Instance()->reset();
    m_gameObjects.clear();

    return true;
}

void GameOverState::s_gameOverToMain() {
    Game::Instance()->getStateMachine()->changeState(new MenuState());
}

void GameOverState::s_restartPlay() {
    Game::Instance()->getStateMachine()->changeState(new PlayState());
}
