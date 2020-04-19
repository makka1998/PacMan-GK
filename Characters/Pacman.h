
#ifndef PACMAN_GK_MASTER_PACMAN_H
#define PACMAN_GK_MASTER_PACMAN_H

#include "GameCharacter.h"

class Pacman : public GameCharacter {
private:
    int m_points = 0;
    int m_health = 3;
    double m_powerUpDuration = 5;
    bool m_lastLife = false;

    ///animation Source rects for pacman
    SDL_Rect m_movementSrcRect[3];
    SDL_Rect m_DeathSrcRect[6];

    ///Angle is used to rotate the picture we use as texture to correctly display the direction the character is moving.
    double m_angle = 0;
    ///Center of pacman, used to base the rotation of the texture.
    SDL_Point m_center = {10, 10};

    Uint8 const *m_keyStates = SDL_GetKeyboardState(nullptr);

public:

    Pacman();

    void PickingUpPillHandler(Map &map);

    void setDirection(Map &map);

    void pacmanDeathAnimation();

    void moveToStartPos();

    void setHealth();

    int getHealth() { return m_health; }

    int getPoints() const { return m_points; }

    double getPowerUpDuration() { return m_powerUpDuration; }

    SDL_Rect *getCoords() { return &m_coordinates; }

    void renderCharacter();
};


#endif //PACMAN_GK_MASTER_PACMAN_H
