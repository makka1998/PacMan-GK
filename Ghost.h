//
// Created by Tobias on 30.03.2020.
//

#ifndef PACMAN_GK_MASTER_GHOST_H
#define PACMAN_GK_MASTER_GHOST_H

#include "GameCharacter.h"

class Ghost : public GameCharacter {
protected:
    SDL_Texture* m_texture;
    SDL_Rect m_pacmanPos;
    int m_startingDestination [2];
    direction m_direction = direction::NONE;
    int m_distanceToTarget [2];
    bool m_startingDestinationReached = false;
    std::vector<bool> wayPointsReached;
    std::vector<int> wayPoints;
public:
    Ghost(int x, int y, int wp1, int wp2, int wp3, int wp4, int wp5, int wp6);
    void setDistanceToTarget(int pacmanPos []);
    virtual void getMovementDirection(Map * map);
    virtual void moveCharacter(Map * map);
    virtual void renderCharacter();
    void isCollidingWithPacman(SDL_Rect pacman);
};


#endif //PACMAN_GK_MASTER_GHOST_H
