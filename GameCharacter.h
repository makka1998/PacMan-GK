//
// Created by Tobias on 28.03.2020.
//

#ifndef PACMAN_GK_MASTER_GAMECHARACTER_H
#define PACMAN_GK_MASTER_GAMECHARACTER_H

#include <SDL.h>
#include <SDL_image.h>
#include "GameManager.h"

/**
 *An enum used to represent the different directions all the gameCharacters can move.
 */
enum class direction {
    NONE,
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class GameCharacter {
protected:
    direction m_direction = direction::NONE;
    SDL_Rect m_coordinates;
    SDL_Texture *m_texture;
    ///Animation number is used to keep track of which frame of the animation we are on.
    int m_animationNumber;
    int m_speed;
    ///Angle is used to rotate the picture we use as texture to correctly display the direction the character is moving.
    double m_angle = 0;
    ///Center of pacman, used to base the rotation of the texture.
    SDL_Point m_center = {10, 10};
public:

    GameCharacter(int xs, int ys, int speed);

    void moveCharacter(int speed);

    bool isColliding(SDL_Rect character, SDL_Rect tile);

    void collisionHandling(Map &map);

    std::vector<bool> pathAvailable(Map &map);

    void setDirection(direction dir);

    virtual void renderCharacter(SDL_Rect srect[]) {};
};


#endif //PACMAN_GK_MASTER_GAMECHARACTER_H
