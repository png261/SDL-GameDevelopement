#include <SDL2/SDL_image.h>

#include "TextureManager.h"

TextureManager* TextureManager::s_pInstance = NULL;

TextureManager::TextureManager() {}

bool TextureManager::load(std::string fileName, std::string id, SDL_Renderer* pRenderer) {
    SDL_Surface* pTempSureFace = IMG_Load(fileName.c_str());
    if(pTempSureFace == NULL) {
        return false;
    }

    SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSureFace);
    SDL_FreeSurface(pTempSureFace);

    if(pTexture == NULL) {
        return false;
    }

    m_textureMap[id] = pTexture;
    return true;
}

void TextureManager::draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip) {
   SDL_Rect srcRect;  
   SDL_Rect destRect;  

   srcRect.x = 0; 
   srcRect.y = 0; 
   srcRect.w = destRect.w = width; 
   srcRect.h = destRect.h = height; 

   destRect.x = x;
   destRect.y = y;

   SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, flip);
}

void TextureManager::drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* pRenderer, SDL_RendererFlip flip) {
   SDL_Rect srcRect;  
   SDL_Rect destRect;  

   srcRect.x = currentFrame * width; 
   srcRect.y = (currentRow - 1) * height; 
   srcRect.w = destRect.w = width; 
   srcRect.h = destRect.h = height; 

   destRect.x = x;
   destRect.y = y;

   SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, flip);
}

void TextureManager::drawTile(std::string id, int margin, int spacing, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer *pRenderer) {
   SDL_Rect srcRect;  
   SDL_Rect destRect;  

   srcRect.x = margin + (spacing + width) * currentFrame;
   srcRect.y = margin + (spacing + height) * currentRow;
   srcRect.w = destRect.w = width;
   srcRect.h = destRect.h = height;

   destRect.x = x;
   destRect.y = y;

   SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, SDL_FLIP_NONE);
}

void TextureManager::clearFromTextureMap(std::string id) {
    m_textureMap.erase(id);
}

void TextureManager::clean() {
    m_textureMap.clear();
}
