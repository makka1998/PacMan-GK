#ifndef PACMAN_GK_MASTER_BLUEGHOST_H
#define PACMAN_GK_MASTER_BLUEGHOST_H

#include "Ghost.h"
class BlueGhost : public Ghost {
private:

public:
    BlueGhost(int xs, int ys, int xr, int yr, int wp1, int wp2, int wp3, int wp4, int wp5, int wp6);

    void getMovementDirection(Map & map) override;
    void renderCharacter(Pacman & pMan) override;
    void doWaypointPath();
};


#endif //PACMAN_GK_MASTER_BLUEGHOST_H
