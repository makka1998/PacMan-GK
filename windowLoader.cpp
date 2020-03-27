#include "windowLoader.h"
#include <iostream>

SDL_Window* windowLoader::createWindow(const char* title)
{
	SDL_Window* window = nullptr; 
	window = SDL_CreateWindow(
		title,
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		WIDTH,
		HEIGHT,
		SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL
	);

	if (window == nullptr)
	{
		std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
		SDL_Quit(); // Rydde opp!
	}

	return window;
}
