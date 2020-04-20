#include "SoundManager.h"


/** AudioInitializer runs the Mixer library OpenAudio which lets you use chunksize, in our game we chose frequency 44100 which is similar to CD quality, in older games they used lower frequencies.
 *   Since its modern times the increase in frequency has minimal change on the demand for a good computer.
 *   The amount of channels set is 2 basing it off the player using stereo and not mono: Reasoning behind this is that basically every sound device in modern time uses stereo.
 *   Chunksize is set to 4096, setting it to high or to low will have a negative outcome on slower computers so we put it in a healthy middle.
 */
void SoundManager::audioInitializer() {
    int audioInit = Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
    if (audioInit < 0 || SDL_Init(SDL_INIT_AUDIO) < 0) {
        printf("SDL_mixer initialization failed! SDL_mixer Error: %s\n", Mix_GetError());
    }
}

/**
 *  Function that plays the Main Menu music, also checks whether music is currently playing on any channel and stops that music to prevent overlapping of sound.
 */
void SoundManager::playMenuMusic() {
    Mix_HaltChannel(-1);
    if (m_menuMusic == nullptr) {
        m_menuMusic = Mix_LoadMUS("../Resources/Sounds/pacman_menu_sound.wav");
    }
    Mix_Volume(-1, 5);
    Mix_VolumeMusic(5);
    Mix_PlayMusic(m_menuMusic, -1);
}

/**
 *  plays the intro sound
 */
void SoundManager::playIntroSound(bool &m_playedOnce) {
    if (m_introSound == nullptr) {
        m_introSound = Mix_LoadWAV("../Resources/Sounds/pacman_intro_sound.wav");
    }
    m_playedOnce = true;
    Mix_PlayChannel(6, m_introSound, 0);
}

/**
 * plays the PacmanDeath sound
 */
void SoundManager::playPacmanDeathSound() {
    if (m_deathSound == nullptr) {
        m_deathSound = Mix_LoadWAV("../Resources/Sounds/pacman_death_sound.wav");
    }
    Mix_PlayChannel(3, m_deathSound, 0);
}

/**
 * plays the pacman eats ghost sound
 */
void SoundManager::playEatenSound() {
    if (m_pacmanEatGhost == nullptr) {
        m_pacmanEatGhost = Mix_LoadWAV("../Resources/Sounds/pacman_eat_ghost_sound.wav");
    }
    Mix_PlayChannel(3, m_pacmanEatGhost, 0);
}

/**
 * plays the pill sound
 * if(Mix_Playing(-1) == 0) checks if any channels are playing a sound, and if not, the eat pill sound effect will be played
 * Reason for this is to prevent overlapping of the sound
 */
void SoundManager::playPillSound() {
    if (m_eatPillSound == nullptr) {
        m_eatPillSound = Mix_LoadWAV("../Resources/Sounds/pacman_eat_pill_sound.wav");
    }
    ///Since you can pick up pills so fast, we need to let the first sound play fully.
    if (Mix_Playing(-1) == 0) {
        Mix_PlayChannel(1, m_eatPillSound, 0);
    }
}

/**
 * plays the Powerpillsound
 */
void SoundManager::playPowerPillSound() {
    Mix_HaltChannel(-1);
    if (m_eatPowerPillSound == nullptr) {
        m_eatPowerPillSound = Mix_LoadWAV("../Resources/Sounds/pacman_powerpellet_sound.wav");
    }
    Mix_PlayChannel(1, m_eatPowerPillSound, 0);
}

void SoundManager::freeAll() {
    Mix_FreeMusic(m_menuMusic);
    Mix_FreeChunk(m_eatPillSound);
    Mix_FreeChunk(m_introSound);
    Mix_FreeChunk(m_deathSound);
    Mix_FreeChunk(m_pacmanEatGhost);
    Mix_FreeChunk(m_eatPowerPillSound);

    m_menuMusic = nullptr;
    m_eatPillSound = nullptr;
    m_introSound = nullptr;
    m_deathSound = nullptr;
    m_pacmanEatGhost = nullptr;
    m_eatPowerPillSound = nullptr;
}