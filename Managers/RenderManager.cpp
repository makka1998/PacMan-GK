#include "RenderManager.h"
#include <iostream>

SDL_Renderer* RenderManager::createRenderer(SDL_Window* window)
{

    GameManager::renderer = SDL_CreateRenderer(window, -1, 0);

    /// Short check to see if anything failed
    if (GameManager::renderer == nullptr)
    {
        std::cerr << "Failed to create renderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit(); /// Cleanup
    }

    return GameManager::renderer;
}
