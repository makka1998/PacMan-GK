#ifndef PACMAN_GK_COLLISIONMANAGER_H
#define PACMAN_GK_COLLISIONMANAGER_H

#include "../Map.h"
///Forward Declaration
enum class direction;

class CollisionManager {
public:;

    void collisionHandling(Map &map, SDL_Rect &m_coordinates, direction &m_direction);
};


#endif //PACMAN_GK_COLLISIONMANAGER_H
