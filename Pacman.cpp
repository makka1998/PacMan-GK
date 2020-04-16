//
// Created by Tobias on 28.03.2020.
//

#include "Pacman.h"

Pacman::Pacman() {
    m_coordinates.x = 14 * TILE_SIZE;
    m_coordinates.y = 26 * TILE_SIZE;

    m_coordinates.h = TILE_SIZE;
    m_coordinates.w = TILE_SIZE;
}

void Pacman::PickingUpPillHandler(Map &map) {
    int player_X = round((m_coordinates.x + (m_coordinates.w) / 2) / TILE_SIZE);
    int player_Y = round((m_coordinates.y + (m_coordinates.h) / 2) / TILE_SIZE);

    for (auto &tile : map.map) {
        int tile_X = tile.getCoordinates().x / TILE_SIZE;
        int tile_Y = tile.getCoordinates().y / TILE_SIZE;
        if (player_X == tile_X && player_Y == tile_Y) {
            if (tile.getTileValue() == 10) {
                //Plukk opp pillene
                m_point += 1;
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
    m_powerUpDuration += GameManager::deltaTime;
}

void Pacman::renderCharacter(SDL_Rect srect[]) {
    m_texture = IMG_LoadTexture(GameManager::renderer, "../Resources/Old_Tilesets/PacManSpriteSheet_20x20.png");
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
    SDL_RenderCopyEx(GameManager::renderer, m_texture, &srect[m_animationNumber], &m_coordinates, angle, &center,
                     SDL_FLIP_NONE);
    SDL_DestroyTexture(m_texture);
}

void Pacman::checkMovementInput(Map & map) {
    SDL_PumpEvents();
    if (m_keyStates[SDL_SCANCODE_W] || m_keyStates[SDL_SCANCODE_UP]) {
        if (m_direction != direction::UP) {
            if (pathAvailable(map).at(0)) {
                m_last_direction = m_direction;
                m_direction = direction::UP;
            }
        }
    } else if (m_keyStates[SDL_SCANCODE_S] || m_keyStates[SDL_SCANCODE_DOWN]) {
        if (m_direction != direction::DOWN) {
            if (pathAvailable(map).at(1)) {
                m_last_direction = m_direction;
                m_direction = direction::DOWN;
            }
        }
    } else if (m_keyStates[SDL_SCANCODE_D] || m_keyStates[SDL_SCANCODE_RIGHT]) {
        if (m_direction != direction::RIGHT) {
            if (pathAvailable(map).at(3)) {
                m_last_direction = m_direction;
                m_direction = direction::RIGHT;
            }
        }
    } else if (m_keyStates[SDL_SCANCODE_A] || m_keyStates[SDL_SCANCODE_LEFT]) {
        if (m_direction != direction::LEFT) {
            if (pathAvailable(map).at(2)) {
                m_last_direction = m_direction;
                m_direction = direction::LEFT;
            }
        }
    }
}

void Pacman::ripPacman(SDL_Rect srect[]) {
    int deathPosition = TILE_SIZE * 10;
    m_texture = IMG_LoadTexture(GameManager::renderer, "../Resources/Old_Tilesets/PacManSpriteSheet_20x20.png");
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

SDL_Rect *Pacman::getCoords() {
    return &m_coordinates;
}

void Pacman::playPillSound() {
    m_eatPillSound = Mix_LoadWAV("../Resources/EatPillSound3.wav");
    if (m_eatPillSound == nullptr) {
        printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
    }
    if (Mix_Playing(-1) == 0) {
        //Play the music
        Mix_PlayChannel(1, m_eatPillSound, 0);
    }
}

void Pacman::playPowerPillSound() {
    Mix_HaltChannel(-1);
    m_eatPowerPillSound = Mix_LoadWAV("../Resources/pacman_powerpill.wav");
    if (m_eatPowerPillSound == nullptr) {
        printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
    }
        Mix_PlayChannel(1, m_eatPowerPillSound, 0);
}

void Pacman::startPos() {
    if(!m_lastLife){
        m_coordinates.x = 14 * TILE_SIZE;
        m_coordinates.y = 26 * TILE_SIZE;
    }
        m_direction = direction::NONE;
}

void Pacman::setHealth() {
    m_lastLife = false;
    m_pacHealth -= 1;
    if (m_pacHealth == 0) {
        m_lastLife = true;
    }

}
