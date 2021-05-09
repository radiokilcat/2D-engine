#include <SDL2/SDL.h>
#include <iostream>

#include "res_path.h"
#include "cleanup.h"

const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;

void logSDLError(std::ostream &os, const std::string &msg)
{
    os << msg << " error: " << SDL_GetError() << std::endl;
}

SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *renderer)
{
    SDL_Texture* texture = nullptr;
    SDL_Surface* loadedImage = SDL_LoadBMP(file.c_str());
    if (loadedImage != nullptr)
    {
        texture = SDL_CreateTextureFromSurface(renderer, loadedImage);
        SDL_FreeSurface(loadedImage);
        if (texture == nullptr)
        {
            logSDLError(std::cout, "CreateTextureFromSurface");
        }
    }
    else {
        logSDLError(std::cout, "LoadBMP");
    }
    return texture;
}

void renderTexture(SDL_Texture* texture, SDL_Renderer* renderer, int x, int y)
{
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;

    SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);
    SDL_RenderCopy(renderer, texture, NULL, &dst);
}

int main()
{
    std::cout << "Resource path is: " << getResourcePath() << std::endl;

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
        logSDLError(std::cout, "SDL_Init");
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow(
        "isometric-test",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        640,
        480,
        0
    );

    if (window == nullptr){
        logSDLError(std::cout, "CreateWindow");
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (renderer == nullptr){
        logSDLError(std::cout, "CreateRenderer");
        cleanup(window);
        SDL_Quit();
        return 1;
    }

    std::string resPath = getResourcePath("");
    SDL_Texture* background = loadTexture(resPath + "background.bmp", renderer);
    SDL_Texture* image = loadTexture(resPath + "image.bmp", renderer);
    if (background == nullptr || image == nullptr){
        cleanup(background, image, renderer, window);
        SDL_Quit();
        return 1;
    }

    for (int i = 0; i < 3; ++i){
        //First clear the renderer
        SDL_RenderClear(renderer);

        int bW, bH;
        SDL_QueryTexture(background, NULL, NULL, &bW, &bH);
        for (int y = 0; y < 2; ++y)
        {
            for (int x = 0; x < 2; ++x)
            {
                renderTexture(background, renderer, x*bW, y*bH);
            }
        }
        int iW, iH;
        SDL_QueryTexture(image, NULL, NULL, &iW, &iH);
        renderTexture(image, renderer, SCREEN_WIDTH / 2 - iW / 2, SCREEN_HEIGHT / 2 - iH / 2);

        SDL_RenderPresent(renderer);
        SDL_Delay(1000);
    }
    cleanup(background, image, renderer, window);
    SDL_Quit();

    return 0;
}
