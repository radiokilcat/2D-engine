#include <SDL_image.h>
#include <SDL_ttf.h>
#include "texturemanager.h"

TextureManager::TextureManager()
{
}

bool TextureManager::loadTexture(std::string filename, std::string id, SDL_Renderer *renderer)
{
    SDL_Texture* texture = IMG_LoadTexture(renderer, filename.c_str());
    if (texture != 0)
    {
        texture_map_[id] = texture;
        return true;
    }
    return false;
}

void TextureManager::draw(std::string id, int x, int y, int width, int height, SDL_Renderer *renderer, SDL_RendererFlip flip)
{

}

void TextureManager::drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer *renderer, SDL_RendererFlip flip)
{

}


