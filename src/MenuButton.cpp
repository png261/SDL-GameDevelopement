#include "MenuButton.h"
#include "InputHandler.h"
#include <SDL2/SDL.h>

MenuButton::MenuButton() : SDLGameObject()
{
}

void MenuButton::load(const LoaderParams* pParams) {

    SDLGameObject::load(pParams);
    m_callbackID = pParams->getCallbackID();
    m_currentFrame = MOUSE_OUT;
}

void MenuButton::draw() {
    SDLGameObject::draw();
}

void MenuButton::update() {
    Vector2D* pMousePos = InputHandler::Instance()->getMousePosition();
    bool isOver = (pMousePos->getX() < (m_position.getX() + m_width)
            && pMousePos->getX() > m_position.getX()
            && pMousePos->getY() < (m_position.getY() + m_height)
            && pMousePos->getY() > m_position.getY());

    if(isOver) {
        m_currentFrame = MOUSE_OVER;
        if(InputHandler::Instance()->getMouseButtonState(LEFT)) {
            m_currentFrame = CLICKED;
            m_callback();
            m_bReleased = false;
        }
    } else {
        m_bReleased = true;
        m_currentFrame = MOUSE_OUT;
    }
}

void MenuButton::clean() {
    SDLGameObject::clean();
}
