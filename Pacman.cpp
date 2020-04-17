//
// Created by Tobias on 28.03.2020.
//

#include "Pacman.h"

Pacman::Pacman() : GameCharacter(13, 26, 200) {
}

/**
 * If u walk over any kind of pill sets the tile you walked over to a blank tile.
 * What kind of pill you walked over will determine what sound plays, and if you get a power up or not.
 * @param map Container with all the tiles the level is made up of.
 */
void Pacman::PickingUpPillHandler(Map &map) {
    int player_X = round((m_coordinates.x + (m_coordinates.w) / 2) / TILE_SIZE);
    int player_Y = round((m_coordinates.y + (m_coordinates.h) / 2) / TILE_SIZE);

    ///Checking every tile to see if you walked over it.
    for (auto &tile : map.map) {
        int tile_X = tile.getCoordinates().x / TILE_SIZE;
        int tile_Y = tile.getCoordinates().y / TILE_SIZE;
        if (player_X == tile_X && player_Y == tile_Y) {
            if (tile.getTileValue() == 10) {
                m_points += 1;
                tile.setTileValue(0);
                tile.WalkedOver = true;
                playPillSound();
            } else if (tile.getTileValue() == 9) {
                tile.setTileValue(0);
                tile.WalkedOver = true;
                m_powerUpDuration = 0;
                playPowerPillSound();
            }
    }
    }
    ///For every call it increases the powerUpDuration, but sets it zero when you walk over a power pellet. This way you will have a power up while m_powerUpDuration is less than some value.
    m_powerUpDuration += GameManager::deltaTime;
}

/**
 * Sets the texture of pacman to correctly show which direction it is traveling.
 * @param srect An array of SDL_Rects that contains the different places in the spritesheet we have to look to get the correct pacman graphic.
 */
void Pacman::renderCharacter(SDL_Rect srect[]) {
    m_texture = IMG_LoadTexture(GameManager::renderer, "../Resources/Images/PacManSpriteSheet_20x20.png");
    ///Using a timer to display the correct part of the animation.
    m_timer += GameManager::deltaTime;
    if (m_timer <= 0.1) {
        m_animationNumber = 0;
        srect[0].x = TILE_SIZE;
        srect[0].y = TILE_SIZE;
        srect[0].h = TILE_SIZE;
        srect[0].w = TILE_SIZE;
    } else if (m_timer <= 0.2) {
        m_animationNumber = 1;
        srect[1].x = 0;
        srect[1].y = TILE_SIZE;
        srect[1].h = TILE_SIZE;
        srect[1].w = TILE_SIZE;
    } else if (m_timer <= 0.3) {
        m_animationNumber = 2;
        srect[2].x = TILE_SIZE * 2;
        srect[2].y = 0;
        srect[2].h = TILE_SIZE;
        srect[2].w = TILE_SIZE;
        if (m_timer <= 0.4) {
            m_timer = 0;
        }
    }
    SDL_RenderCopyEx(GameManager::renderer, m_texture, &srect[m_animationNumber], &m_coordinates, m_angle, &m_center,
                     SDL_FLIP_NONE);
    SDL_DestroyTexture(m_texture);
}

/**
 * Keeps track of if any of the movement keys have been pressed. Will only change to the corresponding direction when it is an open tile.
 * @param map Container with all the tiles the level is made up of.
 */
void Pacman::checkMovementInput(Map &map) {
    SDL_PumpEvents();
    if (m_keyStates[SDL_SCANCODE_W] || m_keyStates[SDL_SCANCODE_UP]) {
        if (pathAvailable(map).at(0)) {
            m_direction = direction::UP;
        }

    } else if (m_keyStates[SDL_SCANCODE_S] || m_keyStates[SDL_SCANCODE_DOWN]) {
        if (pathAvailable(map).at(1)) {
            m_direction = direction::DOWN;
        }

    } else if (m_keyStates[SDL_SCANCODE_D] || m_keyStates[SDL_SCANCODE_RIGHT]) {
        if (pathAvailable(map).at(3)) {
            m_direction = direction::RIGHT;
        }

    } else if (m_keyStates[SDL_SCANCODE_A] || m_keyStates[SDL_SCANCODE_LEFT]) {
        if (pathAvailable(map).at(2)) {
            m_direction = direction::LEFT;
        }
    }
}

/**
 * Progressively cycles through the death animation of pacman.
 * @param srect An array of SDL_Rects that contains the different places in the spritesheet we have to look to get the correct pacman graphic.
 */
void Pacman::ripPacman(SDL_Rect srect[]) {
    int deathPosition = TILE_SIZE * 10;
    m_texture = IMG_LoadTexture(GameManager::renderer, "../Resources/Images/PacManSpriteSheet_20x20.png");
    ///Using a timer to display the correct part of the animation.
    m_timer += GameManager::deltaTime;
    if (m_timer <= 0) {
        m_animationNumber = 0;
        srect[0].x = TILE_SIZE * 0;
        srect[0].y = deathPosition;
        srect[0].h = TILE_SIZE;
        srect[0].w = TILE_SIZE;
    } else if (m_timer <= 0.8) {
        m_animationNumber = 1;
        srect[1].x = TILE_SIZE * 2;
        srect[1].y = deathPosition;
        srect[1].h = TILE_SIZE;
        srect[1].w = TILE_SIZE;
    } else if (m_timer <= 1.6) {
        m_animationNumber = 2;
        srect[2].x = TILE_SIZE * 4;
        srect[2].y = deathPosition;
        srect[2].h = TILE_SIZE;
        srect[2].w = TILE_SIZE;
    } else if (m_timer <= 2.4) {
        m_animationNumber = 3;
        srect[3].x = TILE_SIZE * 6;
        srect[3].y = deathPosition;
        srect[3].h = TILE_SIZE;
        srect[3].w = TILE_SIZE;
    } else if (m_timer <= 3.2) {
        m_animationNumber = 4;
        srect[4].x = TILE_SIZE * 8;
        srect[4].y = deathPosition;
        srect[4].h = TILE_SIZE;
        srect[4].w = TILE_SIZE;
    } else if (m_timer <= 4) {
        m_animationNumber = 5;
        srect[5].x = TILE_SIZE * 9;
        srect[5].y = deathPosition;
        srect[5].h = TILE_SIZE;
        srect[5].w = TILE_SIZE;
    }
    SDL_RenderCopy(GameManager::renderer, m_texture, &srect[m_animationNumber], &m_coordinates);
    SDL_DestroyTexture(m_texture);
}

void Pacman::playPillSound() {
    auto eatPillSound = Mix_LoadWAV("../Resources/Sounds/pacman_eat_pill_sound.wav");
    if (eatPillSound == nullptr) {
        printf("Failed to load pill eating sound ! SDL_mixer Error: %s\n", Mix_GetError());
    }
    ///Since you can pick up pills so fast, we need to let the first sound play fully.
    if (Mix_Playing(-1) == 0) {
        //Play the music
        Mix_PlayChannel(1, eatPillSound, 0);
    }
}

void Pacman::playPowerPillSound() {
    Mix_HaltChannel(-1);
    auto eatPowerPillSound = Mix_LoadWAV("../Resources/Sounds/pacman_powerpellet_sound.wav");
    if (eatPowerPillSound == nullptr) {
        printf("Failed to load eat power pellet SDL_mixer Error: %s\n", Mix_GetError());
    }
    Mix_PlayChannel(1, eatPowerPillSound, 0);
}

/**
 * If pacman is not on his last life, it return him to his start position.
 */
void Pacman::startPos() {
    if (!m_lastLife) {
        m_coordinates.x = 14 * TILE_SIZE;
        m_coordinates.y = 26 * TILE_SIZE;
    }
    m_direction = direction::NONE;
}

/**
 * Reduces pacman's health with one.
 */
void Pacman::setHealth() {
    m_pacHealth -= 1;
    if (m_pacHealth == 0) {
        m_lastLife = true;
    }

}
