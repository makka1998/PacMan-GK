#include "SoundManager.h"

/** AudioInitializer runs the Mixer library OpenAudio which lets you use chunksize, in our game we chose frequency 44100 which is similar to CD quality, in older games they used lower frequencies.
 *   Since its modern times the increase in frequency has minimal change on the demand for a good computer.
 *   The amount of channels set is 2 basing it off the player using stereo and not mono: Reasoning behind this is that basically every sound device in modern time uses stereo.
 *   Chunksize is set to 4096, setting it to high or to low will have a negative outcome on slower computers so we put it in a healthy middle.
 */
void SoundManager::audioInitializer() {
    int audioInit = Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
    if (audioInit < 0) {
        printf("SDL_mixer initialization failed! SDL_mixer Error: %s\n", Mix_GetError());
    }
}

/**
 *  Function that plays the Main Menu music, also checks whether music is currently playing on any channel and stops that music to prevent overlapping of sound.
 */
void SoundManager::playMenuMusic() {
    if (Mix_Playing(-1)) {
        Mix_HaltChannel(-1);
    }
    auto menuMusic = Mix_LoadWAV("../Resources/Sounds/pacman_menu_sound.wav");
    if (menuMusic == nullptr) {
        printf("Failed to load menu sound effect! SDL_mixer Error: %s\n", Mix_GetError());
    }
    Mix_Volume(-1, 5);
    Mix_PlayChannel(6, menuMusic, -1);
}

/// Function that plays the intro sound
void SoundManager::playIntroSound(bool &m_playedOnce) {

    Mix_HaltChannel(6);
    auto introSound = Mix_LoadWAV("../Resources/Sounds/pacman_intro_sound.wav");
    if (introSound == nullptr) {
        printf("Failed to load intro sound effect! SDL_mixer Error: %s\n", Mix_GetError());
    }
    m_playedOnce = true;
    Mix_PlayChannel(6, introSound, 0);
}

void SoundManager::playPacmanDeathSound() {
    auto death = Mix_LoadWAV("../Resources/Sounds/pacman_death_sound.wav");
    if (death == nullptr) {
        std::cout << "Could not play death sound!" << std::endl;
    }
    Mix_PlayChannel(3, death, 0);
}

void SoundManager::playEatenSound() {
    auto pacmanEatGhost = Mix_LoadWAV("../Resources/Sounds/pacman_eat_ghost_sound.wav");
    if (pacmanEatGhost == nullptr) {
        std::cout << "Could not play eat ghost sound!" << std::endl;
    }
    Mix_PlayChannel(3, pacmanEatGhost, 0);
}

/**
 * plays the pill sound
 * if(Mix_Playing(-1) == 0) checks if any channels are playing a sound, and if not, the eat pill sound effect will be played
 * Reason for this is to prevent overlapping of the sound
 */
void SoundManager::playPillSound() {
    Mix_Chunk *eatPillSound = Mix_LoadWAV("../Resources/Sounds/pacman_eat_pill_sound.wav");
    if (eatPillSound == nullptr) {
        printf("Failed to load pill eating sound ! SDL_mixer Error: %s\n", Mix_GetError());
    }
    ///Since you can pick up pills so fast, we need to let the first sound play fully.
    if (Mix_Playing(-1) == 0) {
        Mix_PlayChannel(1, eatPillSound, 0);
    } else {
        Mix_FreeChunk(eatPillSound);
        eatPillSound = nullptr;
    }
}
/**
 * plays the Powerpillsound
 */
void SoundManager::playPowerPillSound() {
    Mix_HaltChannel(-1);
    auto eatPowerPillSound = Mix_LoadWAV("../Resources/Sounds/pacman_powerpellet_sound.wav");
    if (eatPowerPillSound == nullptr) {
        printf("Failed to load eat power pellet SDL_mixer Error: %s\n", Mix_GetError());
    }
    Mix_PlayChannel(1, eatPowerPillSound, 0);
}