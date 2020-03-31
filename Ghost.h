//
// Created by Tobias on 30.03.2020.
//

#ifndef PACMAN_GK_MASTER_GHOST_H
#define PACMAN_GK_MASTER_GHOST_H

#include "GameCharacter.h"

class Ghost : public GameCharacter {
protected:
    SDL_Texture* m_texture = IMG_LoadTexture(GameManager::renderer, "../Resources/Real_Pacman_UP.png");
    SDL_Rect m_pacmanPos;
    int m_distanceToTarget [2];
public:
    Ghost();
    void setDistanceToTarget(SDL_Rect pacmanPos);
    void getMovementDirection(Map * map);
    virtual void moveCharacter(Map * map) ;
    virtual void renderCharacter()  ;
};


#endif //PACMAN_GK_MASTER_GHOST_H
