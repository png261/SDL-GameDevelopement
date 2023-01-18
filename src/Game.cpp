#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Game.h"
#include "InputHandler.h"
#include "MenuState.h"
#include "PlayState.h"

Game* Game::s_pInstance = NULL;

bool Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen) {
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        SDL_Log("SDL init fail");
        return false;
    }

    m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, fullscreen ? SDL_WINDOW_FULLSCREEN : 0);
    if(m_pWindow == NULL) {
        SDL_Log("Window init fail");
        return false;
    }

    m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
    if(m_pRenderer == NULL) {
        SDL_Log("Renderer init fail");
        return false;
    }

    m_pGameStateMachine = new GameStateMachine();
    m_pGameStateMachine->changeState(new MenuState());

    TextureManager::Instance()->load("assets/animate-alpha.png", "animate", m_pRenderer);

    m_gameObjects.push_back(new Player(new LoaderParams(100, 100, 128, 82, "animate")));
    m_gameObjects.push_back(new Enemy(new LoaderParams(300, 300, 128, 82, "animate")));

    m_bRunning = true;

    return true;
}

void Game::handleEvents() {
    InputHandler::Instance()->update();
    if(InputHandler::Instance()->isKeyDown(SDL_SCANCODE_RETURN)) {
        m_pGameStateMachine->changeState(new PlayState());
    }
} 

void Game::update() {
    m_pGameStateMachine->update();
}

void Game::render() {
    SDL_RenderClear(m_pRenderer);

    m_pGameStateMachine->render();

    SDL_RenderPresent(m_pRenderer);
}

void Game::clean() {
    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);
    SDL_Quit();
}

