//
// Created by Tobias on 08.04.2020.
//

#include "RedGhost.h"
RedGhost::RedGhost(int xs, int ys, int xr, int yr, int wp1, int wp2, int wp3, int wp4, int wp5, int wp6) : Ghost(xs, ys, xr, yr, wp1, wp2, wp3, wp4, wp5, wp6) {
}

void RedGhost::getMovementDirection(Map &map) {
    int ghost_x = floor(m_coordinates.x / TILE_SIZE);
    int ghost_y = floor(m_coordinates.y / TILE_SIZE);

    if (!m_startingDestinationReached) {
        timer = 0;
        if(ghost_x < wayPoints.at(0) && !(wayPointsReached.at(0))){
            m_direction = direction::RIGHT;
            if(ghost_x == wayPoints.at(0) - 1){
                wayPointsReached.at(0) = true;
            }
        } else if (ghost_y > wayPoints.at(1) && !(wayPointsReached.at(1))) {
            m_direction = direction::UP;
            if(ghost_y == wayPoints.at(1) + 1){
                wayPointsReached.at(1) = true;
            }
        } else if (ghost_x > wayPoints.at(2) && !(wayPointsReached.at(2))) {
            m_direction = direction::LEFT;
            if(ghost_x == wayPoints.at(2) + 1){
                wayPointsReached.at(2) = true;
            }
        }  else if (ghost_y > wayPoints.at(3) && !(wayPointsReached.at(3))) {
            m_direction = direction::UP;
            if(ghost_y == wayPoints.at(3) + 1){
                wayPointsReached.at(3) = true;
            }
        } else if (ghost_x> wayPoints.at(4) && !(wayPointsReached.at(4))) {
            m_direction = direction::LEFT;
            if(ghost_x == wayPoints.at(4) + 1){
                wayPointsReached.at(4) = true;
            }
        } else if (ghost_y > wayPoints.at(5) && !(wayPointsReached.at(5))) {
            m_direction = direction::UP;
            if(ghost_y == wayPoints.at(5) + 1){
                wayPointsReached.at(5) = true;
            } else {
                m_startingDestinationReached = true;
            }
        }
    } else {
        timer += GameManager::deltaTime;
        if (timer >= 1.5) {
            v1 = rand() % 4 + 1;
            timer = 0;
        }

        switch (v1) {
            case 1 :
                if (pathAvailable(map).at(0) && m_direction != direction::DOWN) {
                    if (m_direction != direction::UP) {
                        m_last_direction = m_direction;
                    }
                    m_direction = direction::UP;
                } else {
                    v1 = 2;
                }
                break;
            case 2 :
                if (pathAvailable(map).at(1) && m_direction != direction::UP) {
                    if (m_direction != direction::DOWN) {
                        m_last_direction = m_direction;
                    }
                    m_direction = direction::DOWN;
                } else {
                    v1 = 3;
                }
                break;
            case 3 :
                if (pathAvailable(map).at(2) && m_direction != direction::RIGHT) {
                    if (m_direction != direction::LEFT) {
                        m_last_direction = m_direction;
                    }
                    m_direction = direction::LEFT;
                } else {
                    v1 = 4;
                }
                break;
            case 4 :
                if (pathAvailable(map).at(3) && m_direction != direction::LEFT) {
                    if (m_direction != direction::RIGHT) {
                        m_last_direction = m_direction;
                    }
                    m_direction = direction::RIGHT;
                } else {
                    v1 = 1;
                }
                break;
        }
    }

    //std::cout << "Pacman : " << "X " <<m_pacmanPos.x << ", Y " <<m_pacmanPos.y << std::endl;
    //std::cout << "Ghost : " << "X " <<ghost_x << ", Y " <<ghost_y << std::endl;

}

void RedGhost::getPacmanCoords(SDL_Rect *pacmanCoords) {
    m_pacmanPos.x = floor(pacmanCoords->x / TILE_SIZE);
    m_pacmanPos.y = floor(pacmanCoords->y / TILE_SIZE);
    //m_pacmanPos.x= pacmanCoords->x;
    //m_pacmanPos.y= pacmanCoords->y;
}

void RedGhost::renderCharacter(Pacman & pMan) {
    m_texture = IMG_LoadTexture(GameManager::renderer, "../Resources/Old_Tilesets/PacManSpriteSheet_20x20.png");
    SDL_Rect srect;
    srect.y = 4 * TILE_SIZE;
    srect.x = 0;
    srect.h = TILE_SIZE;
    srect.w = TILE_SIZE;
    if(m_direction == direction::LEFT){
        srect.x = 2 * TILE_SIZE;
    }
    if(m_direction == direction::DOWN){
        srect.x = TILE_SIZE;
    }
    if(m_direction == direction::RIGHT){
        srect.x = 3 * TILE_SIZE;
    }
    if(pMan.getPowerUpDuration() < 5){
        srect.x = 0;
        srect.y = 8 * TILE_SIZE;
    }
    SDL_RenderCopy(GameManager::renderer, m_texture, &srect, &m_coordinates);
    SDL_DestroyTexture(m_texture);
}