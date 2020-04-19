#ifndef PACMAN_GK_SOUNDMANAGER_H
#define PACMAN_GK_SOUNDMANAGER_H

#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL.h"
#include <iostream>

class SoundManager {
private:
    Mix_Music *menuMusic = nullptr;
    Mix_Chunk *eatPillSound = nullptr;
    Mix_Chunk *introSound = nullptr;
    Mix_Chunk *deathSound = nullptr;
    Mix_Chunk *pacmanEatGhost = nullptr;
    Mix_Chunk *eatPowerPillSound = nullptr;
public:
    SoundManager();

    void audioInitializer();

    void playMenuMusic();

    void playIntroSound(bool &m_playedOnce);

    void playPacmanDeathSound();

    void playEatenSound();

    void playPillSound();

    void playPowerPillSound();

    void FreeAll();
};


#endif //PACMAN_GK_SOUNDMANAGER_H
