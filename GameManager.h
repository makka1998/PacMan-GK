#ifndef PAC_MAN_GK_GAMEMANAGER_H
#define PAC_MAN_GK_GAMEMANAGER_H
#include "windowLoader.h"
#include "renderManager.h"
#include "Map.h"
#include <iostream>
#include <SDL.h>

class OrangeGhost;
class OrangeGhost;

class GameManager {
public:
	int startGame();
	static SDL_Renderer * renderer;
	bool running;
    void render();
private:
    SDL_Rect srect [12];

    void PointsToTextureHandler(int points);

    void showGrid();
};

#endif //PACMAN_GK_MASTER_GAMEMANAGER_H

