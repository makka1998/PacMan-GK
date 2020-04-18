#ifndef PACMAN_GK_COLLISIONMANAGER_H
#define PACMAN_GK_COLLISIONMANAGER_H

#include "../Map.h"

enum class direction;
class CollisionManager {
private:
    bool isColliding(SDL_Rect player, SDL_Rect tile);
public:;

    void collisionHandling(Map &map, SDL_Rect &m_coordinates, direction &m_direction);
};


#endif //PACMAN_GK_COLLISIONMANAGER_H
