
#ifndef PACMAN_GK_MOVEMENTMANAGER_H
#define PACMAN_GK_MOVEMENTMANAGER_H


#include <SDL_rect.h>
#include <vector>
#include "../Map.h"

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

class MovementManager {

public:
    void moveCharacter(int &m_speed, SDL_Rect &m_coordinates, direction &m_direction);

    std::vector<bool> pathAvailable(Map &map, SDL_Rect &m_coordinates);
};


#endif //PACMAN_GK_MOVEMENTMANAGER_H
