#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>

class Game {
    public:
        Game() {};
        ~Game() {};

        bool init(const char *title, int x, int y, int w, int h, bool fullscreen);
        void render();
        void update();
        void handleEvents();
        void clean();

        bool running() { return m_bRunning; }
    private:
        SDL_Window* m_pWindow;
        SDL_Renderer* m_pRenderer;

        SDL_Texture* m_pTexture;
        SDL_Rect m_sourceRectangle;
        SDL_Rect m_destinationRectangle;

        bool m_bRunning;
};

#endif


