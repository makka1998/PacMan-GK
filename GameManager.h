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
	bool running;
    void render();

private:
    SDL_Texture* drawable;
    SDL_Rect coords;
    eventHandler chiefInspector;

    bool isColliding(SDL_Rect player, SDL_Rect tile);
    int poeng=0;
    void collison();
};

#endif //PACMAN_GK_MASTER_GAMEMANAGER_H

