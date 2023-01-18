#include "SDLGameObject.h"
#include "Game.h"
#include "TextureManager.h"

SDLGameObject::SDLGameObject(const LoaderParams* pParams) :
    GameObject(pParams), m_position(pParams->getX(), pParams->getY()), m_velocity(0, 0)
{
    m_width = pParams->getWidth();
    m_height = pParams->getHeight();
    m_textureID = pParams->getTextureID();
    m_numFrames = pParams->getNumFrames();
    m_currentRow = 1;
    m_currentFrame = 1;
}

void SDLGameObject::draw()
{
    SDL_RendererFlip flagsFlip = m_velocity.getX() > 0 ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    TextureManager::Instance()->drawFrame(m_textureID, m_position.getX(), m_position.getY(), m_width, m_height, m_currentRow, m_currentFrame, Game::Instance()->getRenderer(), flagsFlip);
}

void SDLGameObject::update()
{
    m_velocity += m_acceleration;
    m_position += m_velocity;
}

void SDLGameObject::clean()
{
}

