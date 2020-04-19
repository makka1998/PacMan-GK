#include "RedGhost.h"
#include "../../Managers/GameManager.h"

RedGhost::RedGhost(int x, int y, int wp1, int wp2, int wp3, int wp4, int wp5, int wp6) : Ghost(x, y, wp1, wp2, wp3, wp4, wp5, wp6) {
}

void RedGhost::doWaypointPath() {
    int ghost_x = floor(m_coordinates.x / TILE_SIZE);
    int ghost_y = floor(m_coordinates.y / TILE_SIZE);

    if (ghost_x <= m_wayPoints.at(0) && !(m_wayPointsReached.at(0))) {
        m_direction = direction::RIGHT;
        if (ghost_x == m_wayPoints.at(0) ) {
            m_wayPointsReached.at(0) = true;
        }
    } else if (ghost_y >= m_wayPoints.at(1) && !(m_wayPointsReached.at(1))) {
        m_direction = direction::UP;
        if (ghost_y == m_wayPoints.at(1) ) {
            m_wayPointsReached.at(1) = true;
        }
    } else if (ghost_x >= m_wayPoints.at(2) && !(m_wayPointsReached.at(2))) {
        m_direction = direction::LEFT;
        if (ghost_x == m_wayPoints.at(2)) {
            m_wayPointsReached.at(2) = true;
        }
    } else if (ghost_y >= m_wayPoints.at(3) && !(m_wayPointsReached.at(3))) {
        m_direction = direction::UP;
        if (ghost_y == m_wayPoints.at(3)) {
            m_wayPointsReached.at(3) = true;
        }
    } else if (ghost_x >= m_wayPoints.at(4) && !(m_wayPointsReached.at(4))) {
        m_direction = direction::LEFT;
        if (ghost_x == m_wayPoints.at(4)) {
            m_wayPointsReached.at(4) = true;
        }
    } else if (ghost_y >= m_wayPoints.at(5) && !(m_wayPointsReached.at(5))) {
        m_direction = direction::UP;
        if (ghost_y == m_wayPoints.at(5)) {
            m_wayPointsReached.at(5) = true;
        } else {
            m_startingDestinationReached = true;
        }
    }
}
void RedGhost::renderCharacter(Pacman &pMan) {
    m_texture = IMG_LoadTexture(GameManager::renderer, "../Resources/Images/PacManSpriteSheet_20x20.png");
    SDL_Rect srect;
    srect.y = 4 * TILE_SIZE;
    srect.h = TILE_SIZE;
    srect.w = TILE_SIZE;

    if (m_direction == direction::LEFT) {
        srect.x = 2 * TILE_SIZE;
    }
    if (m_direction == direction::DOWN) {
        srect.x = TILE_SIZE;
    }
    if (m_direction == direction::RIGHT) {
        srect.x = 3 * TILE_SIZE;
    }
    if (pMan.getPowerUpDuration() < 5) {
        srect.x = 0;
        srect.y = 8 * TILE_SIZE;
    }
    SDL_RenderCopy(GameManager::renderer, m_texture, &srect, &m_coordinates);
    SDL_DestroyTexture(m_texture);
}