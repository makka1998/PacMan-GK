#pragma once
#include <SDL.h>
class renderManager {
public:
	SDL_Renderer* createRenderer(SDL_Window* window);
};

