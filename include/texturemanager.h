#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <string>
#include <map>
#include <SDL2/SDL.h>

class TextureManager
{
public:
    TextureManager();
    bool loadTexture(std::string filename, std::string id, SDL_Renderer* renderer);
    void draw(std::string id, int x, int y, int width, int height,
              SDL_Renderer* renderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void drawFrame(std::string id, int x, int y, int width, int height,
              int currentRow, int currentFrame,
              SDL_Renderer* renderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
private:
    std::map<std::string, SDL_Texture*> texture_map_;
};

#endif // TEXTUREMANAGER_H
