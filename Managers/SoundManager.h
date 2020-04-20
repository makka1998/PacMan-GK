#ifndef PACMAN_GK_SOUNDMANAGER_H
#define PACMAN_GK_SOUNDMANAGER_H

#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL.h"
#include <iostream>

class SoundManager {
private:
    Mix_Music *m_menuMusic = nullptr;
    Mix_Chunk *m_eatPillSound = nullptr;
    Mix_Chunk *m_introSound = nullptr;
    Mix_Chunk *m_deathSound = nullptr;
    Mix_Chunk *m_pacmanEatGhost = nullptr;
    Mix_Chunk *m_eatPowerPillSound = nullptr;
public:
    void audioInitializer();

    void playMenuMusic();

    void playIntroSound(bool &m_playedOnce);

    void playPacmanDeathSound();

    void playEatenSound();

    void playPillSound();

    void playPowerPillSound();

    void freeAll();
};


#endif //PACMAN_GK_SOUNDMANAGER_H
