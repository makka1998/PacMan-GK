#include "RenderManager.h"
#include <iostream>

SDL_Renderer* RenderManager::createRenderer(SDL_Window* window)
{

    GameManager::renderer = SDL_CreateRenderer(window, -1, 0);

    // Sjekke om noe gikk galt
    if (GameManager::renderer == nullptr)
    {
        std::cerr << "Failed to create renderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window); SDL_Quit(); // rydde opp
    }

    return GameManager::renderer;
}
