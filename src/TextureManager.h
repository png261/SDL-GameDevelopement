#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <SDL2/SDL.h>
#include <map>
#include <string>

class TextureManager {
  public:
    static TextureManager *Instance() {
        static TextureManager *s_pInstance = new TextureManager();
        return s_pInstance;
    }
    bool load(std::string filename, std::string id, SDL_Renderer *pRenderer);
    void draw(std::string id, int x, int y, int width, int height,
              SDL_Renderer *pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void drawTile(std::string id, int margin, int spacing, int x, int y,
                  int width, int height, int currentRow, int currentFrame,
                  SDL_Renderer *pRenderer);
    void drawFrame(std::string id, int x, int y, int width, int height,
                   int currentRow, int currentFrame, SDL_Renderer *pRenderer,
                   SDL_RendererFlip flip = SDL_FLIP_NONE);
    void clearFromTextureMap(std::string id);
    void clean();

  private:
    TextureManager();
    std::map<std::string, SDL_Texture *> m_textureMap;
};

#endif
