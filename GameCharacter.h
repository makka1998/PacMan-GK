//
// Created by Tobias on 28.03.2020.
//

#ifndef PACMAN_GK_MASTER_GAMECHARACTER_H
#define PACMAN_GK_MASTER_GAMECHARACTER_H

#include <SDL.h>
#include <SDL_image.h>
#include "GameManager.h"

enum class direction{
    NONE,
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class GameCharacter {
protected:
    Uint8 const* m_keyStates = SDL_GetKeyboardState(nullptr);
    Uint8 const* m_last_keyStates;
    direction m_direction = direction::UP;
    direction m_last_direction = direction::UP;
    SDL_Rect m_coordinates;
    SDL_Texture * m_texture;
public:
    GameCharacter();
    virtual void checkMovementInput();
    virtual void moveCharacter(Map * map);
    bool isColliding(SDL_Rect character, SDL_Rect tile);
    void collisionHandling(Map * map);
    void renderCharacter(SDL_Rect srect [], int testTall);
    bool pathAvailable(Map *map);
};


#endif //PACMAN_GK_MASTER_GAMECHARACTER_H
