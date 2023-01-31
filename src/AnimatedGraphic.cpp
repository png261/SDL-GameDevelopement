#include "AnimatedGraphic.h"
#include "InputHandler.h"
#include <SDL2/SDL.h>

AnimatedGraphic::AnimatedGraphic() : SDLGameObject() {}

void AnimatedGraphic::load(const LoaderParams *pParams) {
    SDLGameObject::load(pParams);
}

void AnimatedGraphic::draw() { SDLGameObject::draw(); }

void AnimatedGraphic::update() {
    if (m_numFrames > 0) {
        m_currentFrame = int(((
            SDL_GetTicks() / (1000 / std::min(m_animSpeed, 1)) % m_numFrames)));
    }
}

void AnimatedGraphic::clean() { SDLGameObject::clean(); }
