//
// Created by Tobias on 08.04.2020.
//

#include "PinkGhost.h"

PinkGhost::PinkGhost(int x, int y, int wp1, int wp2, int wp3, int wp4, int wp5, int wp6) : Ghost(x, y, wp1, wp2, wp3, wp4, wp5, wp6) {

}

void PinkGhost::getMovementDirection(Map *map) {
    if (!m_startingDestinationReached) {
        if(m_coordinates.x / TILE_SIZE < wayPoints.at(0) && !(wayPointsReached.at(0))){
            m_direction = direction::RIGHT;
            if(m_coordinates.x / TILE_SIZE == wayPoints.at(0) - 1){
                wayPointsReached.at(0) = true;
            }
        } else if (m_coordinates.y / TILE_SIZE > wayPoints.at(1) && !(wayPointsReached.at(1))) {
            m_direction = direction::UP;
            if(m_coordinates.y / TILE_SIZE == wayPoints.at(1) + 1){
                wayPointsReached.at(1) = true;
            }
        } else if (m_coordinates.x / TILE_SIZE > wayPoints.at(2) && !(wayPointsReached.at(2))) {
            m_direction = direction::LEFT;
            if(m_coordinates.x / TILE_SIZE == wayPoints.at(2) + 1){
                wayPointsReached.at(2) = true;
            }
        }  else if (m_coordinates.y / TILE_SIZE < wayPoints.at(3) && !(wayPointsReached.at(3))) {
            m_direction = direction::DOWN;
            if(m_coordinates.y / TILE_SIZE == wayPoints.at(3) - 1){
                wayPointsReached.at(3) = true;
            }
        } else if (m_coordinates.x / TILE_SIZE > wayPoints.at(4) && !(wayPointsReached.at(4))) {
            m_direction = direction::LEFT;
            if(m_coordinates.x / TILE_SIZE == wayPoints.at(4) + 1){
                wayPointsReached.at(4) = true;
            }
        } else if (m_coordinates.y / TILE_SIZE < wayPoints.at(5) && !(wayPointsReached.at(5))) {
            m_direction = direction::DOWN;
            if(m_coordinates.y / TILE_SIZE == wayPoints.at(5) - 1){
                wayPointsReached.at(5) = true;
            }
        } else {
            m_startingDestinationReached = true;
        }
    } else {
        if (pathAvailable(map).at(2) && m_direction != direction::RIGHT) {
            if(m_direction != direction::LEFT){
                m_last_direction = m_direction;
                m_direction = direction::LEFT;
            }
        } else if (pathAvailable(map).at(3) && m_direction != direction::LEFT) {
            if(m_direction != direction::RIGHT){
                m_last_direction = m_direction;
                m_direction = direction::RIGHT;
            }
        } else if (pathAvailable(map).at(0) && m_direction != direction::DOWN) {
            if(!(m_last_direction == direction::DOWN && m_direction == direction::RIGHT)){
                if(m_direction != direction::UP){
                    m_last_direction = m_direction;
                    m_direction = direction::UP;
                }
            } else {
                m_direction = direction::DOWN;
            }
        } else if (pathAvailable(map).at(1) && m_direction != direction::UP) {
            if(!(m_last_direction == direction::UP && m_direction == direction::LEFT)){
                if(m_direction != direction::DOWN){
                    m_last_direction = m_direction;
                    m_direction = direction::DOWN;
                }
            } else {
                m_direction = direction::RIGHT;
            }
        }
    }
}

void PinkGhost::renderCharacter() {
    m_texture = IMG_LoadTexture(GameManager::renderer, "../Resources/Old_Tilesets/PacManSpriteSheet_20x20.png");
    SDL_Rect srect;
    srect.y = 5 * TILE_SIZE;
    srect.x = 0;
    srect.h = TILE_SIZE;
    srect.w = TILE_SIZE;
    SDL_RenderCopy(GameManager::renderer, m_texture, &srect, &m_coordinates);
}