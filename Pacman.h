//
// Created by Tobias on 28.03.2020.
//

#ifndef PACMAN_GK_MASTER_PACMAN_H
#define PACMAN_GK_MASTER_PACMAN_H

#include "GameCharacter.h"

class Pacman : public GameCharacter {
private:
    SDL_Texture* m_texture = IMG_LoadTexture(GameManager::renderer, "../Resources/Pacman_16x16_Tileset_Blue.png");
    int point = 1;
    int pacHealth = 3;
    double m_powerUpDuration = 5;
public:
    Pacman();
    int getHealth() { return pacHealth;}
    int getPoints() const { return point;}
    double getPowerUpDuration(){return m_powerUpDuration;}
    direction getDirection();
    void setDirection(direction dir);
    void setHealth(){ pacHealth -= 1;}
    void setPoints(int resetPoints){ point = resetPoints;}
    void PickingUpPillHandler(Map &map);
    SDL_Rect * getCoords();
    void renderCharacter(SDL_Rect *srect) override;
    void ripPacman(SDL_Rect *srect);

    void startPos();
};


#endif //PACMAN_GK_MASTER_PACMAN_H
