#ifndef PACMAN_GK_MASTER_BLUEGHOST_H
#define PACMAN_GK_MASTER_BLUEGHOST_H

#include "../Ghost.h"

class BlueGhost : public Ghost {
public:
    BlueGhost(int x, int y, int wp1, int wp2, int wp3, int wp4, int wp5, int wp6);

    void doWaypointPath();

    void renderCharacter(Pacman &pMan) override;
};


#endif //PACMAN_GK_MASTER_BLUEGHOST_H
