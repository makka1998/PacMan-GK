#ifndef PAC_MAN_GK_GAMEMANAGER_H
#define PAC_MAN_GK_GAMEMANAGER_H
#include "windowLoader.h"
#include "renderManager.h"
#include "Map.h"
#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL2/SDL_mixer.h>


class OrangeGhost;
class Pacman;

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

    int playSound();
};

#endif //PACMAN_GK_MASTER_GAMEMANAGER_H

