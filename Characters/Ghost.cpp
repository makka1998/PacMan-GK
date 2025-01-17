#include "Ghost.h"
#include "../Managers/GameManager.h"

///Using the parent class's constructor for it's none unique variables.
Ghost::Ghost(int x, int y, int wp1, int wp2, int wp3, int wp4, int wp5, int wp6) : m_wayPoints{wp1, wp2, wp3, wp4, wp5,wp6},
                                                                                   m_startingPosition{x, y},
                                                                                   GameCharacter(x, y, 140) {
}

/**
 * Choosing a direction at random, if that direction isn't available it switches to another one.
 * @param map Container with all the tiles the level is made up of.
 */
void Ghost::chooseRandomDirection(Map &map) {
    srand(time(NULL));
    ///A timer is used to avoid switching direction too often.
    m_timer += GameManager::deltaTime;
    if (m_timer >= 1.5) {
        m_randomDirection = rand() % 4 + 1;
        m_timer = 0;
    }
    switch (m_randomDirection) {
        case 1 :
            ///To avoid it turning back and forth or up and down endlessly, we dont allow the "AI" to choose a direction that is opposite of it's current direction. (LEFT & RIGHT) (UP & DOWN)
            if (m_movementManager.pathAvailable(map, m_coordinates).at(0) && m_direction != direction::DOWN) {
                m_direction = direction::UP;
            } else {
                m_randomDirection = 2;
            }
            break;
        case 2 :
            if (m_movementManager.pathAvailable(map, m_coordinates).at(1) && m_direction != direction::UP) {
                m_direction = direction::DOWN;
            } else {
                m_randomDirection = 3;
            }
            break;
        case 3 :
            if (m_movementManager.pathAvailable(map, m_coordinates).at(3) && m_direction != direction::LEFT) {
                m_direction = direction::RIGHT;
            } else {
                m_randomDirection = 4;
            }
            break;
        case 4 :
            if (m_movementManager.pathAvailable(map, m_coordinates).at(2) && m_direction != direction::RIGHT) {
                m_direction = direction::LEFT;
            } else {
                m_randomDirection = 1;
            }
            break;
    }
}

/**
 * Checks if the ghost is ever inn contact with Pacman, if it is, two things will happen depending on Pacman having the power up buff or not.
 * @param pMan A reference to the pacman game object.
 * @param gameCharacters A reference to all the ghosts.
 * @param map Container with all the tiles the level is made up of.
 */
void
Ghost::pacmanGhostCollisionManager(Pacman &pMan, const std::vector<std::shared_ptr<Ghost>> &gameCharacters, Map &map) {
    if (SDL_HasIntersection(&m_coordinates, pMan.getCoords()) && pMan.getPowerUpDuration() < 5) {
        m_soundManager.playEatenSound();
        moveToStartPos();
    } else if (SDL_HasIntersection(&m_coordinates, pMan.getCoords())) {
        m_soundManager.playPacmanDeathSound();
        pMan.setHealth();
        pMan.moveToStartPos();
        ///Changes the health indicator to correctly display the number of health pacman has.
        for (auto &tile : *map.getMap()) {
            if (tile.getCoordinates().x == 60 && tile.getCoordinates().y == 700 && pMan.getHealth() == 2) {
                tile.setTileValue(0);
                tile.setWalkedOver(true);
            } else if (tile.getCoordinates().x == 40 && tile.getCoordinates().y == 700 && pMan.getHealth() == 1) {
                tile.setTileValue(0);
                tile.setWalkedOver(true);
            } else if (tile.getCoordinates().x == 20 && tile.getCoordinates().y == 700 && pMan.getHealth() == 0) {
                tile.setTileValue(0);
                tile.setWalkedOver(true);
            }
        }
        ///Returns all the ghosts to start.
        for (const auto &ghost : gameCharacters) {
            ghost->moveToStartPos();
        }
    }
}

/**
 * If the ghost has completed it's first set of non dynamic movement it will start wandering random.
 * @param map Container with all the tiles the level is made up of.
 */
void Ghost::getMovementDirection(Map &map) {
    if (!m_startingDestinationReached) {
        doWaypointPath();
    } else {
        chooseRandomDirection(map);
    }
}

void Ghost::moveToStartPos() {
    m_coordinates.x = m_startingPosition[0] * TILE_SIZE;
    m_coordinates.y = m_startingPosition[1] * TILE_SIZE;
    m_startingDestinationReached = false;
    for (auto &&wp : m_wayPointsReached) {
        wp = false;
    }
}

void Ghost::frightenMode(Pacman &pMan, SDL_Rect &srect) {
    /// Turn blue when powerpill effect is active and start blinking when its 1 second left.
    if (pMan.getPowerUpDuration() < 4) {
        srect.x = 0;
        srect.y = 8 * TILE_SIZE;
    }
    if (pMan.getPowerUpDuration() >= 4 && pMan.getPowerUpDuration() <= 4.25) {
        srect.x = 1 * TILE_SIZE;
        srect.y = 8 * TILE_SIZE;
    } else if (pMan.getPowerUpDuration() >= 4.25 && pMan.getPowerUpDuration() <= 4.5) {
        srect.x = 0 * TILE_SIZE;
        srect.y = 8 * TILE_SIZE;
    } else if (pMan.getPowerUpDuration() >= 4.5 && pMan.getPowerUpDuration() <= 4.75) {
        srect.x = 1 * TILE_SIZE;
        srect.y = 8 * TILE_SIZE;
    } else if (pMan.getPowerUpDuration() >= 4.75 && pMan.getPowerUpDuration() <= 5) {
        srect.x = 0 * TILE_SIZE;
        srect.y = 8 * TILE_SIZE;
    }
}


