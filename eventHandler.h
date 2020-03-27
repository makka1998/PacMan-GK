//
// Created by Tobias on 26.03.2020.
//
#ifndef PACMAN_GK_MASTER_EVENTHANDLER_H
#define PACMAN_GK_MASTER_EVENTHANDLER_H
#include <SDL.h>
#include <iostream>
#include "TextureManager.h"

enum class direction{
    NONE,
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class eventHandler {
private:
    TextureManager textureManager;
    Uint8 const* keyStates = SDL_GetKeyboardState(nullptr);
    direction _direction = direction::NONE;
public:
    void checkMovementInput();
    void moveCharacter(SDL_Rect& coordinates, SDL_Texture*& texture, SDL_Renderer* tegemann);
    void getDirection();
};


#endif //PACMAN_GK_MASTER_EVENTHANDLER_H
