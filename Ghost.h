#ifndef PACMAN_GK_MASTER_GHOST_H
#define PACMAN_GK_MASTER_GHOST_H

#include "GameCharacter.h"
#include "Pacman.h"

class Ghost : public GameCharacter {
protected:
    ///An array where index 0 is x-coordinate and index 1 is y-coordinate.
    int m_startingPosition[2];
    ///A variable used to determine which direction the ghost will wander.
    int m_randomDirection = 1;
    bool m_startingDestinationReached = false;

    std::vector<bool> m_wayPointsReached = {false, false, false, false, false, false};
    std::vector<int> m_wayPoints;

public:
    Ghost(int x, int y, int wp1, int wp2, int wp3, int wp4, int wp5, int wp6);

    void wanderRandom(Map &map);

    void isCollidingWithPacman(Pacman &pMan, const std::vector<std::shared_ptr<Ghost>> &gameCharacters, Map &map);

    void moveToStartPos();

    void playDeathSound();

    void playEatenSound();

    virtual void getMovementDirection(Map &map) {};

    virtual void renderCharacter(Pacman &pMan) {};
};


#endif //PACMAN_GK_MASTER_GHOST_H
