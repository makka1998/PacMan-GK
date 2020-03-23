#pragma once
#include <SDL.h>
class windowLoader {
public:
	SDL_Window* createWindow(const char* title, int width, int height);
};

