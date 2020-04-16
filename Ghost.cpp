#include "Ghost.h"

Ghost::Ghost(int xs, int ys, int xr, int yr, int wp1, int wp2, int wp3, int wp4, int wp5, int wp6) {
    m_coordinates.x = xs * TILE_SIZE;
    m_coordinates.y = ys * TILE_SIZE;

    m_coordinates.h = TILE_SIZE;
    m_coordinates.w = TILE_SIZE;

    m_startingPosition[0] = xs;
    m_startingPosition[1] = ys;

    m_respawnPosition[0] = xr;
    m_respawnPosition[1] = yr;
    wayPointsReached = {false, false, false, false, false, false, false};
    wayPoints = {wp1, wp2, wp3, wp4, wp5, wp6};
    setDistanceToTarget(m_startingPosition);
}


void Ghost::wanderRandom(Map &map) {
    //Random seed
    srand(time(NULL));
    m_timer += GameManager::deltaTime;
    if (m_timer >= 1.5) {
        m_RNG = rand() % 4 + 1;
        m_timer = 0;
    }
    switch (m_RNG) {
        case 1 :
            if (pathAvailable(map).at(0) && m_direction != direction::DOWN) {
                if (m_direction != direction::UP) {
                    m_last_direction = m_direction;
                }
                m_direction = direction::UP;
            } else {
                m_RNG = 2;
            }
            break;
        case 2 :
            if (pathAvailable(map).at(1) && m_direction != direction::UP) {
                if (m_direction != direction::DOWN) {
                    m_last_direction = m_direction;
                }
                m_direction = direction::DOWN;
            } else {
                m_RNG = 3;
            }
            break;
        case 3 :
            if (pathAvailable(map).at(3) && m_direction != direction::LEFT) {
                if (m_direction != direction::RIGHT) {
                    m_last_direction = m_direction;
                }
                m_direction = direction::RIGHT;
            } else {
                m_RNG = 4;
            }
            break;
        case 4 :
            if (pathAvailable(map).at(2) && m_direction != direction::RIGHT) {
                if (m_direction != direction::LEFT) {
                    m_last_direction = m_direction;
                }
                m_direction = direction::LEFT;
            } else {
                m_RNG = 1;
            }
            break;
    }
}

void Ghost::setDistanceToTarget(int startingDest[]) {
    m_distanceToTarget[0] = startingDest[0] - m_coordinates.x / TILE_SIZE;
    m_distanceToTarget[1] = startingDest[1] - m_coordinates.y / TILE_SIZE;
}

void Ghost::isCollidingWithPacman(Pacman &pMan, const std::vector<std::shared_ptr<Ghost>> &gameCharacters, Map &map) {
    if (SDL_HasIntersection(&m_coordinates, pMan.getCoords()) && pMan.getPowerUpDuration() < 5) {
        playEatenSound();
        m_coordinates.x = m_respawnPosition[0] * TILE_SIZE;
        m_coordinates.y = m_respawnPosition[1] * TILE_SIZE;
    } else if (SDL_HasIntersection(&m_coordinates, pMan.getCoords())) {
        playDeathSound();
        pMan.setHealth();
        pMan.startPos();
        for (auto &tile : map.map) {
            if (tile.getCoordinates().x == 60 && tile.getCoordinates().y == 700 && pMan.getHealth() == 2) {
                tile.setTileValue(0);
                tile.WalkedOver = true;
            } else if (tile.getCoordinates().x == 40 && tile.getCoordinates().y == 700 && pMan.getHealth() == 1) {
                tile.setTileValue(0);
                tile.WalkedOver = true;
            } else if (tile.getCoordinates().x == 20 && tile.getCoordinates().y == 700 && pMan.getHealth() == 0) {
                tile.setTileValue(0);
                tile.WalkedOver = true;
            }
        }
        //set ghost position
        for (const auto &ghost : gameCharacters) {
            ghost->moveToRespawnPos();
        }
    }
}

void Ghost::renderCharacter(Pacman &pMan) {

}

void Ghost::moveToRespawnPos() {
    m_coordinates.x = m_respawnPosition[0] * TILE_SIZE;
    m_coordinates.y = m_respawnPosition[1] * TILE_SIZE;
}

void Ghost::playDeathSound() {
    auto death = Mix_LoadWAV("../Resources/pacman_death.wav");
    if (death == nullptr) {
        std::cout << "Could not play death sound!" << std::endl;
    }
    Mix_PlayChannel(3, death, 0);
}

void Ghost::playEatenSound() {
    auto pacmanEatGhost = Mix_LoadWAV("../Resources/pacman_eatghost.wav");
    if (pacmanEatGhost == nullptr) {
        std::cout << "Could not play death sound!" << std::endl;
    }
    Mix_PlayChannel(3, pacmanEatGhost, 0);
}
