//
// Created by Tobias on 26.03.2020.
//

#include "TextureManager.h"

SDL_Texture* TextureManager::createTexture(const char * imagePath, SDL_Renderer* renderer)
{
    SDL_Surface* surface = IMG_Load(imagePath);
    if (surface == nullptr)
    {
        std::cerr << "Failed to load image: " << SDL_GetError() << std::endl;
        SDL_DestroyRenderer(renderer);
        SDL_Quit();
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

