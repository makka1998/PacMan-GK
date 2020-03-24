#include <SDL.h>

class textureManager {
public:
	SDL_Texture* createTexture(const char* imagePath, SDL_Renderer* renderer);
};
