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

    /**Container to store the different coordinates on the x and y-axis it has to move.
    * The coordinates stored is only kept with the value corresponding to the axis movement has to happen on.
    * If it needs to do a left turn followed by going up, the container will only have two numbers, one representing the point it has to reach on the x-axis and the same for y-axis in that order.
    */
    std::vector<int> m_wayPoints;

public:
    Ghost(int x, int y, int wp1, int wp2, int wp3, int wp4, int wp5, int wp6);

    void chooseRandomDirection(Map &map);

    void getMovementDirection(Map &map);

    void pacmanGhostCollisionManager(Pacman &pMan, const std::vector<std::shared_ptr<Ghost>> &gameCharacters, Map &map);

    void moveToStartPos();

    virtual void doWaypointPath(){};

    virtual void renderCharacter(Pacman &pMan) {};

    void frightenMode(Pacman &pMan, SDL_Rect &srect);
};


#endif //PACMAN_GK_MASTER_GHOST_H
