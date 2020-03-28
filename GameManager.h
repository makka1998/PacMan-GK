#ifndef PAC_MAN_GK_GAMEMANAGER_H
#define PAC_MAN_GK_GAMEMANAGER_H
#include "windowLoader.h"
#include "renderManager.h"
#include "TextureManager.h"
#include "Map.h"
#include <iostream>
#include <SDL.h>

class Pacman;
class Ghost;

class GameManager {
public:
	int startGame();
	static SDL_Renderer * renderer;
	bool running;
    void render();
private:
    int testTall;
    SDL_Texture* drawable;
    SDL_Rect coords;
};

#endif //PACMAN_GK_MASTER_GAMEMANAGER_H

