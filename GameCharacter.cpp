//
// Created by Tobias on 28.03.2020.
//

#include "GameCharacter.h"
/**
 * Sets the "spawn" location for the gameCharacter.
 * @param xs x-coordinate it starts on.
 * @param ys y-coordinate it starts on.
 */
GameCharacter::GameCharacter(int xs, int ys, int speed){
    m_coordinates = {xs * TILE_SIZE, ys * TILE_SIZE, TILE_SIZE, TILE_SIZE};
    m_speed = speed;
}

/**
 * Depending on which direction the character has, move it that direction.
 * If either the start music is playing or the power pellet pick up sound is playing, dont allow any movement.
 * @param speed The speed the gameCharacter will move at.
 *
 */
void GameCharacter::moveCharacter(int speed) {
    if (Mix_Playing(6) != 0 || Mix_Playing(3) != 0) {}
    else {
        m_speed = speed * GameManager::deltaTime;
        if (m_direction == direction::RIGHT) {
            m_coordinates.x += m_speed;
            m_angle = 0;


        } else if (m_direction == direction::LEFT) {
            m_coordinates.x += -m_speed;
            m_angle = 180;

        } else if (m_direction == direction::UP) {
            m_coordinates.y += -m_speed;
            m_angle = -90;

        } else if (m_direction == direction::DOWN) {
            m_coordinates.y += m_speed;
            m_angle = 90;
        } else if (m_direction == direction::NONE) {
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
 * Checking if any point of a gameCharacter overlaps with any point of the tile.
 * @param player The coordinates of the gameCharacter.
 * @param tile The coordinates of the obstacle.
 * @return true if the gameCharacter coordinates intersects with the obstacles or false if not.
 */
bool GameCharacter::isColliding(SDL_Rect player, SDL_Rect tile) {
    return SDL_HasIntersection(&player, &tile);
}

/**
 * Checking if a gameCharacter collides with an obstacle, if it does it gets pushed back into the playing field. Where to set it after a collision depends on what kind of obstacle it collides with.
 * @param map Container with all the tiles the level is made up of.
 */
void GameCharacter::collisionHandling(Map &map) {
    ///Checking every tile to see if you collided with it.
    for (Tile o : map.map) {
        if (isColliding(m_coordinates, o.getCoordinates())) {
            if (o.getTileValue() == 3) { ///Horizontal obstacles
                if (m_direction == direction::DOWN || m_direction == direction::RIGHT || m_direction == direction::LEFT) {
                    m_coordinates.y = o.getCoordinates().y - TILE_SIZE;
                } else if (m_direction == direction::UP) {
                    m_coordinates.y = o.getCoordinates().y + TILE_SIZE;
                }
            }

            if (o.getTileValue() == 4 || o.getTileValue() == 5) {///Vertical obstacles
                if (m_direction == direction::LEFT) {
                    m_coordinates.x = o.getCoordinates().x + TILE_SIZE;
                } else if (m_direction == direction::RIGHT) {
                    m_coordinates.x = o.getCoordinates().x - TILE_SIZE;
                }
            }

            if (o.getTileValue() == 1 || o.getTileValue() == 11) {///Top-left corner
                if (m_direction == direction::DOWN || m_direction == direction::RIGHT) {
                    m_coordinates.x = o.getCoordinates().x - TILE_SIZE;
                    m_coordinates.y = o.getCoordinates().y - TILE_SIZE;
                }
            }

            if (o.getTileValue() == 2 || o.getTileValue() == 12) {///Top-right corner
                if (m_direction == direction::DOWN || m_direction == direction::LEFT) {
                    m_coordinates.x = o.getCoordinates().x + TILE_SIZE;
                    m_coordinates.y = o.getCoordinates().y - TILE_SIZE;
                }
            }

            if (o.getTileValue() == 7 || o.getTileValue() == 13) {///Bottom-left corner
                if (m_direction == direction::RIGHT || m_direction == direction::UP) {
                    m_coordinates.x = o.getCoordinates().x - TILE_SIZE;
                    m_coordinates.y = o.getCoordinates().y + TILE_SIZE;
                }
            }

            if (o.getTileValue() == 8 || o.getTileValue() == 14) {///Bottom-right corner
                if (m_direction == direction::LEFT || m_direction == direction::UP) {
                    m_coordinates.x = o.getCoordinates().x + TILE_SIZE;
                    m_coordinates.y = o.getCoordinates().y + TILE_SIZE;
                }
            }
        }
    }
}

/**
 * Checks whether or not there is an obstacle in all the directions around you.
 * @param map Container with all the tiles the level is made up of.
 * @return a std::vector of size 4, where each index represents a direction. If a given direction has an available path that index in the vector is set true.
 */
std::vector<bool> GameCharacter::pathAvailable(Map &map) {
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

void GameCharacter::setDirection(direction dir) {
    m_direction = dir;
}

