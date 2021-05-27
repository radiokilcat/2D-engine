#include <SDL_image.h>
#include <SDL_ttf.h>
#include "texturemanager.h"

static TextureManager* instance_;

TextureManager::TextureManager()
{
}

TextureManager* TextureManager::instance()
{
    if(instance_ == 0)
    {
        instance_ = new TextureManager;
        return instance_;
    }
    return instance_;
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

void TextureManager::draw(std::string id, int x, int y,
                          int width, int height,
                          SDL_Renderer *renderer, SDL_RendererFlip flip)
{
    SDL_Rect srcRect;
    SDL_Rect destRect;

    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = destRect.w = width;
    srcRect.h = destRect.h = height;

    destRect.x = x;
    destRect.y = y;

    SDL_RenderCopyEx(renderer, texture_map_[id], &srcRect, &destRect, 0, 0, flip);
}

void TextureManager::drawFrame(std::string id, int x, int y,
                               int width, int height,
                               int currentRow, int currentFrame,
                               SDL_Renderer *renderer, SDL_RendererFlip flip)
{
    SDL_Rect srcRect;
    SDL_Rect destRect;

    srcRect.x = width * currentFrame;
    srcRect.y = height * (currentRow - 1);
    srcRect.w = destRect.w = width;
    srcRect.h = destRect.h = height;

    destRect.x = x;
    destRect.y = y;

    SDL_RenderCopyEx(renderer, texture_map_[id], &srcRect, &destRect, 0, 0, flip);
}


