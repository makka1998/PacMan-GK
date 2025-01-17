#include "WindowLoader.h"
#include <iostream>

/**
 * @param Title is the name of the window we created
 * @return Returns the window created
 */
SDL_Window *WindowLoader::createWindow(const char *title) {
    SDL_Window *window = nullptr;
    window = SDL_CreateWindow(
            title,
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            WIDTH,
            HEIGHT,
            SDL_RENDERER_PRESENTVSYNC
    );

    if (window == nullptr) {
        std::cerr << "Failed to create m_window: " << SDL_GetError() << std::endl;
        SDL_Quit();
    }

    return window;
}
