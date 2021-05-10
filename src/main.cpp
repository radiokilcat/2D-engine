#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>

#include "res_path.h"
#include "cleanup.h"

const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;
const int TILE_SIZE = 40;

void logSDLError(std::ostream &os, const std::string &msg)
{
    os << msg << " error: " << SDL_GetError() << std::endl;
}

SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *renderer)
{
    SDL_Texture* texture = IMG_LoadTexture(renderer, file.c_str());
    if (texture == nullptr)
        logSDLError(std::cout, "CreateTextureFromSurface");

    return texture;
}

void renderTexture(SDL_Texture* texture, SDL_Renderer* renderer, int x, int y, int w, int h)
{
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    dst.w = w;
    dst.h = h;

    SDL_RenderCopy(renderer, texture, NULL, &dst);
}

void renderTexture(SDL_Texture* texture, SDL_Renderer* renderer, int x, int y)
{
    int w, h;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    renderTexture(texture, renderer, x, y, w, h);
}

int main()
{
    std::cout << "Resource path is: " << getResourcePath() << std::endl;

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        logSDLError(std::cout, "SDL_Init");
        return 1;
    }

    if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
    {
        logSDLError(std::cout, "IMG_Init");
        SDL_Quit();
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
    SDL_Texture* background = loadTexture(resPath + "background.png", renderer);
    SDL_Texture* image = loadTexture(resPath + "image.png", renderer);
    if (background == nullptr || image == nullptr){
        cleanup(background, image, renderer, window);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Event e;
    bool quit = false;

    while(!quit){
        while(SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
                quit = true;
            if (e.type == SDL_KEYDOWN)
                quit = true;
            if (e.type == SDL_MOUSEBUTTONDOWN)
                quit = true;
        }
        //First clear the renderer
        SDL_RenderClear(renderer);

        int tilesX = SCREEN_WIDTH / TILE_SIZE;
        int tilesY = SCREEN_HEIGHT / TILE_SIZE;
        for (int tile_index = 0; tile_index < tilesX * tilesY; ++tile_index)
        {
            int x = (tile_index % tilesX) * TILE_SIZE;
            int y = (tile_index / tilesX) * TILE_SIZE;
            std::cout << "tilesX: " << tilesX << std::endl;
            std::cout << "tilesY: " << tilesY << std::endl;
            std::cout << "x : " << x << std::endl;
            std::cout << "y : " << y << std::endl;
            renderTexture(background, renderer, x , y, TILE_SIZE, TILE_SIZE );
        }
        int iW, iH;
        SDL_QueryTexture(image, NULL, NULL, &iW, &iH);
        int x = SCREEN_WIDTH / 2 - iW / 2;
        int y = SCREEN_HEIGHT / 2 - iH / 2;
        renderTexture(image, renderer, x, y);

        SDL_RenderPresent(renderer);
        SDL_Delay(1000);
    }
    cleanup(background, image, renderer, window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}
