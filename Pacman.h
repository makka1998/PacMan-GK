//
// Created by Tobias on 28.03.2020.
//

#ifndef PACMAN_GK_MASTER_PACMAN_H
#define PACMAN_GK_MASTER_PACMAN_H

#include "GameCharacter.h"

class Pacman : public GameCharacter {
private:
    SDL_Texture* m_texture = IMG_LoadTexture(GameManager::renderer, "../Resources/Real_Pacman_UP.png");
    int point = 1;

public:
    Pacman();
    int getPoints() const { return point;}
    void setPoints(int resetPoints){ point = resetPoints; }
    void PickingUpPillHandler(Map &map);
    SDL_Rect getCoords();
    void renderCharacter(SDL_Rect *srect) override;
};


#endif //PACMAN_GK_MASTER_PACMAN_H
