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

    SDL_Surface* mTempSureFace = IMG_Load("assets/animate-alpha.png");
    m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, mTempSureFace);
    SDL_FreeSurface(mTempSureFace);

    m_sourceRectangle.w = 128;
    m_sourceRectangle.h = 82;
    m_sourceRectangle.x = 0;
    m_sourceRectangle.y = 0;

    m_destinationRectangle.w = m_sourceRectangle.w;
    m_destinationRectangle.h = m_sourceRectangle.h;
    m_destinationRectangle.x = 0;
    m_destinationRectangle.y = 0;

    SDL_SetRenderDrawColor(m_pRenderer, 255, 0, 0, 255);

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
    m_sourceRectangle.x = 128 * int((SDL_GetTicks() / 100) % 6);
}

void Game::render() {
    SDL_RenderClear(m_pRenderer);

    SDL_RenderCopy(m_pRenderer, m_pTexture, &m_sourceRectangle, &m_destinationRectangle);
    SDL_RenderCopyEx(m_pRenderer, m_pTexture, &m_sourceRectangle, &m_destinationRectangle, 0, 0, SDL_FLIP_NONE);

    SDL_RenderPresent(m_pRenderer);
}

void Game::clean() {
    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);
    SDL_Quit();
}

