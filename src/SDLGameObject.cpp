#include "SDLGameObject.h"
#include "Game.h"
#include "TextureManager.h"

SDLGameObject::SDLGameObject() : GameObject() {
}

void SDLGameObject::load(const LoaderParams* pParams) {
    m_position = Vector2D(pParams->getX(), pParams->getY());
    m_velocity = Vector2D(0,0);
    m_acceleration = Vector2D(0,0);
    m_width = pParams->getWidth();
    m_height = pParams->getHeight();
    m_textureID = pParams->getTextureID();
    m_currentRow = 1;
    m_currentFrame = 1;
    m_animSpeed = pParams->getAnimSpeed();
    m_numFrames = pParams->getNumFrames();
}

void SDLGameObject::draw() {
    SDL_RendererFlip flagsFlip = m_velocity.getX() > 0 ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    TextureManager::Instance()->drawFrame(m_textureID, m_position.getX(), m_position.getY(), m_width, m_height, m_currentRow, m_currentFrame, Game::Instance()->getRenderer(), flagsFlip);
}

void SDLGameObject::update() {
    m_velocity += m_acceleration;
    m_position += m_velocity;
}

void SDLGameObject::clean() {
}

