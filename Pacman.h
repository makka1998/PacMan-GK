//
// Created by Tobias on 28.03.2020.
//

#ifndef PACMAN_GK_MASTER_PACMAN_H
#define PACMAN_GK_MASTER_PACMAN_H

#include "GameCharacter.h"

class Pacman : public GameCharacter {
private:
    SDL_Texture *m_texture = IMG_LoadTexture(GameManager::renderer,"../Resources/Resources/Old_Tilesets/Pacman_Tileset_20x20.png");
    Mix_Chunk *m_eatPillSound;
    Mix_Chunk *m_eatPowerPillSound;
    int m_point;
    int m_pacHealth = 3;
    double m_powerUpDuration = 5;
    double m_timer = 0;
    bool m_lastLife;

    Uint8 const* m_keyStates = SDL_GetKeyboardState(nullptr);

public:

    Pacman();

    bool islastLife() { return m_lastLife; }

    int getHealth() { return m_pacHealth; }

    int getPoints() const { return m_point; }

    double getPowerUpDuration() { return m_powerUpDuration; }

    void setHealth();

    void PickingUpPillHandler(Map &map);

    SDL_Rect *getCoords();

    void renderCharacter(SDL_Rect *srect) override;

    void ripPacman(SDL_Rect *srect);

    void startPos();

    void playPillSound();

    void playPowerPillSound();

    void checkMovementInput(Map &map);
};


#endif //PACMAN_GK_MASTER_PACMAN_H
