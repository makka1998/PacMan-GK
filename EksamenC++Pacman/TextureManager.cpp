#include "TextureManager.h"

#include <iostream>
#include <SDL_image.h>

SDL_Texture* textureManager::createTexture(const char* imagePath, SDL_Renderer* renderer)
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
