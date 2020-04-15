#include "Ghost.h"

//Fiks denne constructoren så den ser pen ut
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

void Ghost::moveCharacter(Map &map) {
    if (Mix_Playing(6) != 0 || Mix_Playing(3) != 0) {
        //  Denne While loopen fryser spillet på riktig måte men Spøkelset blir ikke med :o -Martin
    } else {
        m_speed = 140 * GameManager::deltaTime;
        //m_speed = 1;
        if (m_direction == direction::RIGHT) {
            m_coordinates.x += m_speed;

        } else if (m_direction == direction::LEFT) {
            m_coordinates.x += -m_speed;

        } else if (m_direction == direction::UP) {
            m_coordinates.y += -m_speed;
        } else if (m_direction == direction::DOWN) {
            m_coordinates.y += m_speed;
        }
    }
}

void Ghost::getMovementDirection(Map &map) {


}

void Ghost::setDistanceToTarget(int startingDest[]) {
    m_distanceToTarget[0] = startingDest[0] - m_coordinates.x / TILE_SIZE;
    m_distanceToTarget[1] = startingDest[1] - m_coordinates.y / TILE_SIZE;
}

int *Ghost::getStartingPosition() {
    return m_startingPosition;
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
            }
        }
        //set ghost position
        for (const auto &ghost : gameCharacters) {
            ghost->moveRespawnPos();
        }
    }
}

void Ghost::renderCharacter(Pacman &pMan) {

}

void Ghost::moveRespawnPos() {
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
