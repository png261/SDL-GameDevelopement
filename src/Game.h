#ifndef GAME_H
#define GAME_H

#include "GameStateMachine.h"
#include <SDL2/SDL.h>

class Game {
  public:
    static Game *Instance() {
        static Game *s_pInstance = new Game();
        return s_pInstance;
    };

    bool init(const char *title, int x, int y, int w, int h, bool fullscreen);
    void render();
    void update();
    void handleEvents();
    void clean();
    void quit() { m_bRunning = false; }

    SDL_Renderer *getRenderer() { return m_pRenderer; }

    int getGameWidth() { return m_gameWidth; }

    int getGameHeight() { return m_gameHeight; }

    bool running() { return m_bRunning; }

  private:
    Game(){};
    ~Game(){};

    SDL_Window *m_pWindow;
    SDL_Renderer *m_pRenderer;
    bool m_bRunning;
    int m_gameWidth;
    int m_gameHeight;
};

#endif
