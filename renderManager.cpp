#include "renderManager.h"
#include <iostream>

SDL_Renderer* renderManager::createRenderer(SDL_Window* window)
{
    SDL_Renderer* renderer = nullptr;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Sjekke om noe gikk galt
    if (renderer == nullptr)
    {
        std::cerr << "Failed to create renderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window); SDL_Quit(); // rydde opp
    }

    return renderer;
}
