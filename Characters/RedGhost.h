
#ifndef PACMAN_GK_REDGHOST_H
#define PACMAN_GK_REDGHOST_H

#include "Ghost.h"

class RedGhost : public Ghost {
public:
    RedGhost(int x, int y, int wp1, int wp2, int wp3, int wp4, int wp5, int wp6);

    void doWaypointPath();

    void renderCharacter(Pacman &pMan) override;
};


#endif //PACMAN_GK_REDGHOST_H
