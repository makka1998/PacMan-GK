#include "MovementManager.h"
#include "../GameCharacter.h"
#include "GameManager.h"

/**
 * Depending on which direction the character has, move it that direction.
 * If either the start music is playing or the power pellet pick up sound is playing, dont allow any movement.
 * @param speed The speed the gameCharacter will move at.
 */
void MovementManager::moveCharacter(int &m_speed, SDL_Rect &m_coordinates, direction &m_direction) {
    if (Mix_Playing(6) != 0 || Mix_Playing(3) != 0) {}
    else {
        int speed = m_speed * GameManager::deltaTime;
        if (m_direction == direction::RIGHT) {
            m_coordinates.x += speed;
        } else if (m_direction == direction::LEFT) {
            m_coordinates.x += -speed;
        } else if (m_direction == direction::UP) {
            m_coordinates.y += -speed;
        } else if (m_direction == direction::DOWN) {
            m_coordinates.y += speed;
        }

        ///Teleport to opposite side when a gameCharacter uses a "tunnel".
        if (m_coordinates.x < 2 && m_coordinates.y == 17 * TILE_SIZE) {
            m_coordinates.x = 29 * TILE_SIZE;
        } else if ((m_coordinates.x < 30.5 * TILE_SIZE && m_coordinates.x > 29.5 * TILE_SIZE) &&
                   m_coordinates.y == 17 * TILE_SIZE) {
            m_coordinates.x = 1 * TILE_SIZE;
        }
    }
}

/**
 * Checks whether or not there is an obstacle in all the directions around you.
 * @param map Container with all the tiles the level is made up of.
 * @return a std::vector of size 4, where each index represents a direction. If a given direction has an available path that index in the vector is set true.
 */
std::vector<bool> MovementManager::pathAvailable(Map &map, SDL_Rect &m_coordinates) {
    std::vector<bool> pathAvailable = {false, false, false, false};
    ///By adding on the height and width onto the gameCharacters coordinates we get the coordinates of it's center instead of top left corner.
    int xCoord = round((m_coordinates.x + (m_coordinates.w / 2)) / TILE_SIZE);
    int yCoord = round((m_coordinates.y + (m_coordinates.h / 2)) / TILE_SIZE);

    for (Tile &o : map.map) {
        if (xCoord + 1 == o.getCoordinates().x / TILE_SIZE && yCoord == o.getCoordinates().y / TILE_SIZE) {
            if (o.getTileValue() == 0 || o.getTileValue() == 9 || o.getTileValue() == 10) {
                pathAvailable.at(3) = true;
            }
        }
        if (xCoord - 1 == o.getCoordinates().x / TILE_SIZE && yCoord == o.getCoordinates().y / TILE_SIZE) {
            if (o.getTileValue() == 0 || o.getTileValue() == 9 || o.getTileValue() == 10) {
                pathAvailable.at(2) = true;
            }
        }
        if (xCoord == o.getCoordinates().x / TILE_SIZE && yCoord + 1 == o.getCoordinates().y / TILE_SIZE) {
            if (o.getTileValue() == 0 || o.getTileValue() == 9 || o.getTileValue() == 10) {
                pathAvailable.at(1) = true;
            }
        }
        if (xCoord == o.getCoordinates().x / TILE_SIZE && yCoord - 1 == o.getCoordinates().y / TILE_SIZE) {
            if (o.getTileValue() == 0 || o.getTileValue() == 9 || o.getTileValue() == 10) {
                pathAvailable.at(0) = true;
            }
        }
    }
    return pathAvailable;
}