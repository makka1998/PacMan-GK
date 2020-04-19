#include "SoundManager.h"

/** AudioInitializer runs the Mixer library OpenAudio which lets you use chunksize, in our game we chose frequency 44100 which is similar to CD quality, in older games they used lower frequencies.
 *   Since its modern times the increase in frequency has minimal change on the demand for a good computer.
 *   The amount of channels set is 2 basing it off the player using stereo and not mono: Reasoning behind this is that basically every sound device in modern time uses stereo.
 *   Chunksize is set to 4096, setting it to high or to low will have a negative outcome on slower computers so we put it in a healthy middle.
 */
SoundManager::SoundManager() {

}

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
    if (menuMusic == nullptr) {
        menuMusic = Mix_LoadMUS("../Resources/Sounds/pacman_menu_sound.wav");
    }
    Mix_Volume(-1, 5);
    Mix_VolumeMusic(5);
    Mix_PlayMusic(menuMusic, -1);
}

/**
 *  plays the intro sound
 */
void SoundManager::playIntroSound(bool &m_playedOnce) {
    if (introSound == nullptr) {
        introSound = Mix_LoadWAV("../Resources/Sounds/pacman_intro_sound.wav");
    }
    m_playedOnce = true;
    Mix_PlayChannel(6, introSound, 0);
}

/**
 * plays the PacmanDeath sound
 */
void SoundManager::playPacmanDeathSound() {
    if (deathSound == nullptr) {
        deathSound = Mix_LoadWAV("../Resources/Sounds/pacman_death_sound.wav");
    }
    Mix_PlayChannel(3, deathSound, 0);
}

/**
 * plays the pacman eats ghost sound
 */
void SoundManager::playEatenSound() {
    if (pacmanEatGhost == nullptr) {
        pacmanEatGhost = Mix_LoadWAV("../Resources/Sounds/pacman_eat_ghost_sound.wav");
    }
    Mix_PlayChannel(3, pacmanEatGhost, 0);
}

/**
 * plays the pill sound
 * if(Mix_Playing(-1) == 0) checks if any channels are playing a sound, and if not, the eat pill sound effect will be played
 * Reason for this is to prevent overlapping of the sound
 */
void SoundManager::playPillSound() {
    if (eatPillSound == nullptr) {
        eatPillSound = Mix_LoadWAV("../Resources/Sounds/pacman_eat_pill_sound.wav");
    }
    ///Since you can pick up pills so fast, we need to let the first sound play fully.
    if (Mix_Playing(-1) == 0) {
        Mix_PlayChannel(1, eatPillSound, 0);
    }
}

/**
 * plays the Powerpillsound
 */
void SoundManager::playPowerPillSound() {
    Mix_HaltChannel(-1);
    if (eatPowerPillSound == nullptr) {
        eatPowerPillSound = Mix_LoadWAV("../Resources/Sounds/pacman_powerpellet_sound.wav");
    }
    Mix_PlayChannel(1, eatPowerPillSound, 0);
}

void SoundManager::FreeAll() {
    Mix_FreeMusic(menuMusic);
    Mix_FreeChunk(eatPillSound);
    Mix_FreeChunk(introSound);
    Mix_FreeChunk(deathSound);
    Mix_FreeChunk(pacmanEatGhost);
    Mix_FreeChunk(eatPowerPillSound);

    menuMusic = nullptr;
    eatPillSound = nullptr;
    introSound = nullptr;
    deathSound = nullptr;
    pacmanEatGhost = nullptr;
    eatPowerPillSound = nullptr;
}