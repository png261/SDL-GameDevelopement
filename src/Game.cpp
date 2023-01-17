#include "Game.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

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

    TextureManager::Instance()->load("assets/animate-alpha.png", "animate", m_pRenderer);

    m_go = new GameObject();
    m_player = new Player();
    m_enemy = new Enemy();

    m_go->load(100, 100, 128, 82, "animate");
    m_player->load(300, 300, 128, 82, "animate");
    m_enemy->load(0, 0, 128, 82, "animate");
    SDL_Log("test");


    m_gameObjects.push_back(m_go);
    m_gameObjects.push_back(m_player);
    m_gameObjects.push_back(m_enemy);
    
    m_bRunning = true;

    return true;
}

void Game::handleEvents() {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                m_bRunning = false;
                break;
        }
    }
} 

void Game::update() {
    for (auto& object : m_gameObjects) {
        object->update();
    }
}

void Game::render() {
    SDL_RenderClear(m_pRenderer);

    for (auto& object : m_gameObjects) {
        object->draw(m_pRenderer);
    }

    SDL_RenderPresent(m_pRenderer);
}

void Game::clean() {
    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);
    SDL_Quit();
}

