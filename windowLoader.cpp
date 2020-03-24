#include "windowLoader.h"
#include <iostream>

SDL_Window* windowLoader::createWindow(const char* title, int width, int height)
{
	SDL_Window* window = nullptr; 
	window = SDL_CreateWindow(
		title,
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		width,
		height,
		SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
	);

	if (window == nullptr)
	{
		std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
		SDL_Quit(); // Rydde opp!
	}

	return window;
}
