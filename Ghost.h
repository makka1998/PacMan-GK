//
// Created by Tobias on 30.03.2020.
//

#ifndef PACMAN_GK_MASTER_GHOST_H
#define PACMAN_GK_MASTER_GHOST_H

#include "GameCharacter.h"

class Ghost : public GameCharacter {
protected:
    SDL_Texture* m_texture = IMG_LoadTexture(GameManager::renderer, "../Resources/Real_Pacman_UP.png");
    int distanceToTarget [2];
    double speed;
public:
    Ghost();
    void setDistanceToTarget(SDL_Rect pacmanPos);
    //virtual void checkMovementInput(Map * map) override;
    virtual void moveCharacter(Map * map) ;
    virtual void renderCharacter()  ;
};


#endif //PACMAN_GK_MASTER_GHOST_H
