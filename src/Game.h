#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <vector>

#include "TextureManager.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"

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

        bool m_bRunning;

        GameObject* m_go;
        GameObject* m_player;
        GameObject* m_enemy;

        std::vector<GameObject*> m_gameObjects;
};

#endif


