
#ifndef PACMAN_GK_MASTER_GAMECHARACTER_H
#define PACMAN_GK_MASTER_GAMECHARACTER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <memory>
#include "Map.h"
#include "CollisionManager.h"
#include "MovementHandler.h"

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
    CollisionManager m_collisionManager;
    MovementHandler m_movementManager;
    direction m_direction = direction::NONE;
    SDL_Rect m_coordinates;
    SDL_Texture *m_texture;
    ///Animation number is used to keep track of which frame of the animation we are on.
    int m_animationNumber;
    int m_speed;
    double m_timer;
public:

    GameCharacter(int xs, int ys, int speed);

    void setDirection(direction dir);

    virtual void renderCharacter(SDL_Rect srect[]) {};

    void characterHandler(Map &map);
};


#endif //PACMAN_GK_MASTER_GAMECHARACTER_H
