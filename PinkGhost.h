
#ifndef PACMAN_GK_MASTER_PINKGHOST_H
#define PACMAN_GK_MASTER_PINKGHOST_H

#include "Ghost.h"

/**
 * Only commenting on the pinkGhost since all the different ghost types are the same with the difference being the graphics and starting path.
 */

class PinkGhost : public Ghost {
public:
    PinkGhost(int x, int y, int wp1, int wp2, int wp3, int wp4, int wp5, int wp6);

    void getMovementDirection(Map &map) override;

    void doWaypointPath();

    void renderCharacter(Pacman &pMan) override;
};


#endif //PACMAN_GK_MASTER_PINKGHOST_H
