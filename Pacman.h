
#ifndef PACMAN_GK_MASTER_PACMAN_H
#define PACMAN_GK_MASTER_PACMAN_H

#include "GameCharacter.h"

class Pacman : public GameCharacter {
private:
    int m_points = 0;
    int m_pacHealth = 3;
    double m_powerUpDuration = 5;
    bool m_lastLife = false;

    ///Angle is used to rotate the picture we use as texture to correctly display the direction the character is moving.
    double m_angle = 0;
    ///Center of pacman, used to base the rotation of the texture.
    SDL_Point m_center = {10, 10};

    Uint8 const *m_keyStates = SDL_GetKeyboardState(nullptr);

public:

    Pacman();

    void PickingUpPillHandler(Map &map);

    void renderCharacter(SDL_Rect *srect) override;

    void checkMovementInput(Map &map);

    void ripPacman(SDL_Rect *srect);

    void playPillSound();

    void playPowerPillSound();

    void moveToStartPos();

    void setHealth();

    int getHealth() { return m_pacHealth; }

    int getPoints() const { return m_points; }

    double getPowerUpDuration() { return m_powerUpDuration; }

    SDL_Rect *getCoords() { return &m_coordinates; }
};


#endif //PACMAN_GK_MASTER_PACMAN_H
