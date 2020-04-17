//
// Created by Tobias on 28.03.2020.
//

#ifndef PACMAN_GK_MASTER_PACMAN_H
#define PACMAN_GK_MASTER_PACMAN_H

#include "GameCharacter.h"

class Pacman : public GameCharacter {
private:
    int m_points;
    int m_pacHealth = 3;
    double m_powerUpDuration = 5;
    double m_timer = 0;
    bool m_lastLife = false;

    Uint8 const *m_keyStates = SDL_GetKeyboardState(nullptr);

public:

    Pacman();

    void PickingUpPillHandler(Map &map);

    void renderCharacter(SDL_Rect *srect) override;

    void checkMovementInput(Map &map);

    void ripPacman(SDL_Rect *srect);

    void playPillSound();

    void playPowerPillSound();

    void startPos();

    void setHealth();

    int getHealth() { return m_pacHealth; }

    int getPoints() const { return m_points; }

    double getPowerUpDuration() { return m_powerUpDuration; }

    SDL_Rect *getCoords() { return &m_coordinates; }
};


#endif //PACMAN_GK_MASTER_PACMAN_H
