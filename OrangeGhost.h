
//
// Created by Tobias on 08.04.2020.
//

#ifndef PACMAN_GK_MASTER_ORANGEGHOST_H
#define PACMAN_GK_MASTER_ORANGEGHOST_H

#include "Ghost.h"

class OrangeGhost : public Ghost{
private:

public:
    OrangeGhost(int x, int y, int wp1, int wp2, int wp3, int wp4, int wp5, int wp6);
    void getMovementDirection(Map * map) override;
    void renderCharacter() override;
};


#endif //PACMAN_GK_MASTER_ORANGEGHOST_H
