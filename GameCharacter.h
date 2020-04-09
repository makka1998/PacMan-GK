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
    direction m_direction = direction::NONE;
    direction m_last_direction = direction::NONE;
    SDL_Rect m_coordinates;
    SDL_Texture * m_texture;
    int m_animationNumber;
    int m_speed;
public:
    GameCharacter();
    virtual void checkMovementInput(Map * map);
    virtual void moveCharacter(Map * map);
    bool isColliding(SDL_Rect character, SDL_Rect tile);
    void collisionHandling(Map * map);
    virtual void renderCharacter(SDL_Rect srect []);
    virtual std::vector<bool> pathAvailable(Map *map);
    double angle = 0;
    SDL_Point center = {10,10};
};


#endif //PACMAN_GK_MASTER_GAMECHARACTER_H
