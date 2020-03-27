#ifndef PAC_MAN_GK_GAMEMANAGER_H
#define PAC_MAN_GK_GAMEMANAGER_H
#include "windowLoader.h"
#include "renderManager.h"
#include "TextureManager.h"
#include "eventHandler.h"
#include "Map.h"
#include <iostream>
#include <SDL.h>
class GameManager {
public:
	int startGame();
	static SDL_Renderer * renderer;
};

#endif //PACMAN_GK_MASTER_GAMEMANAGER_H

