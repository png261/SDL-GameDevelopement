#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Game.h"
#include "AnimatedGraphic.h"
#include "GameOverState.h"
#include "InputHandler.h"
#include "MainMenuState.h"
#include "PlayState.h"
#include "PauseState.h"
#include "MenuButton.h"
#include "GameStateMachine.h"
#include "TextureManager.h"
#include "Player.h"
#include "Enemy.h"

Game* Game::s_pInstance = NULL;

bool Game::init(const char *title, int x, int y, int width, int height, bool fullscreen) {
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        SDL_Log("SDL init fail");
        return false;
    }

    m_pWindow = SDL_CreateWindow(title, x, y, width, height, fullscreen ? SDL_WINDOW_FULLSCREEN : 0);
    if(m_pWindow == NULL) {
        SDL_Log("Window init fail");
        return false;
    }

    m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
    if(m_pRenderer == NULL) {
        SDL_Log("Renderer init fail");
        return false;
    }

    GameObjectFactory::Instance()->registerType("MenuButton", new MenuButtonCreator());
    GameObjectFactory::Instance()->registerType("Player", new PlayerCreator());
    GameObjectFactory::Instance()->registerType("Enemy", new EnemyCreator());
    GameObjectFactory::Instance()->registerType("AnimatedGraphic", new AnimatedGraphicCreator());

    GameStateMachine::Instance()->changeState(new MainMenuState());

    m_bRunning = true;
    return true;
}

void Game::handleEvents() {
    InputHandler::Instance()->update();
} 

void Game::update() {
    GameStateMachine::Instance()->update();
}

void Game::render() {
    SDL_RenderClear(m_pRenderer);

    GameStateMachine::Instance()->render();

    SDL_RenderPresent(m_pRenderer);
}

void Game::clean() {
    GameStateMachine::Instance()->clean();

    InputHandler::Instance()->clean();
    TextureManager::Instance()->clean();

    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);
    SDL_Quit();
}

