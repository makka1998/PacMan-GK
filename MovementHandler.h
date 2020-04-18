//
// Created by jonas on 4/18/2020.
//

#ifndef PACMAN_GK_MOVEMENTHANDLER_H
#define PACMAN_GK_MOVEMENTHANDLER_H


#include <SDL_rect.h>
#include <vector>
#include "Map.h"

enum class direction;

class MovementHandler {

public:
    void moveCharacter(int &m_speed, SDL_Rect &m_coordinates, direction &m_direction);

    std::vector<bool> pathAvailable(Map &map, SDL_Rect &m_coordinates);
};


#endif //PACMAN_GK_MOVEMENTHANDLER_H
