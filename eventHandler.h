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
    Uint8 const* keyStates = SDL_GetKeyboardState(nullptr);
    direction _direction = direction::NONE;
public:
    bool closeGame=false;
    void checkMovementInput();
    void moveCharacter(SDL_Rect& coordinates, SDL_Texture*& texture, SDL_Renderer* tegemann);
    direction getDirection();
    direction last_direction;

    void setDirection(direction dir);
};


#endif //PACMAN_GK_MASTER_EVENTHANDLER_H
