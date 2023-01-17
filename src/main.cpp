#include "Game.h"

int main (int argc, char *argv[])
{
    if(!Game::Instance()->init("Chapter 1", 100, 100, 640, 480, 0)) {;
        SDL_Log("Game init failure");
        return -1;
    }

    while(Game::Instance()->running()) {
        Game::Instance()->handleEvents();
        Game::Instance()->update();
        Game::Instance()->render();

        SDL_Delay(10);
    }
    Game::Instance()->clean();

    return 0;
}
