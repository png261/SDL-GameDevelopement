#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include "GameStateMachine.h"

class Game {
    public:
        static Game* Instance() {
            if(s_pInstance == NULL) {
                s_pInstance = new Game();
            }
            return s_pInstance;
        };

        bool init(const char *title, int x, int y, int w, int h, bool fullscreen);
        void render();
        void update();
        void handleEvents();
        void clean();
        void quit() {
            m_bRunning = false; 
        };
        SDL_Renderer* getRenderer() {
            return m_pRenderer; 
        };

        bool running() { 
            return m_bRunning; 
        }
    private:
        Game(){};
        ~Game() {};

        static Game* s_pInstance;

        SDL_Window* m_pWindow;
        SDL_Renderer* m_pRenderer;
        bool m_bRunning;
};

#endif


