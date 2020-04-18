#ifndef PACMAN_GK_SOUNDMANAGER_H
#define PACMAN_GK_SOUNDMANAGER_H

#include "SDL2/SDL_mixer.h"
#include <iostream>
class SoundManager {
public:
    void audioInitializer();
    void playMenuMusic();
    void playIntroSound(bool &m_playedOnce);

    void playPacmanDeathSound();

    void playEatenSound();

    void playPillSound();

    void playPowerPillSound();
};


#endif //PACMAN_GK_SOUNDMANAGER_H
