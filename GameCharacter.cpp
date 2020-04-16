//
// Created by Tobias on 28.03.2020.
//

#include "GameCharacter.h"

GameCharacter::GameCharacter() {
    m_coordinates.x = 6 * 32;
    m_coordinates.y = 9 * 32;
    m_coordinates.h = 20;
    m_coordinates.w = 20;

}

void GameCharacter::moveCharacter(Map &map, int speed) {
    if (Mix_Playing(6) != 0 || Mix_Playing(3) != 0) {}
    else {
        m_speed = speed * GameManager::deltaTime;
        if (m_direction == direction::RIGHT) {
            m_coordinates.x += m_speed;
            angle = 0;


        } else if (m_direction == direction::LEFT) {
            m_coordinates.x += -m_speed;
            angle = 180;

        } else if (m_direction == direction::UP) {
            m_coordinates.y += -m_speed;
            angle = -90;

        } else if (m_direction == direction::DOWN) {
            m_coordinates.y += m_speed;
            angle = 90;
        } else if (m_direction == direction::NONE) {
        }

        //Teleport when character uses the "tunnels"
        if (m_coordinates.x < 2 && m_coordinates.y == 17 * TILE_SIZE) {
            m_coordinates.x = 29 * TILE_SIZE;
        } else if ((m_coordinates.x < 30.5 * TILE_SIZE && m_coordinates.x > 29.5 * TILE_SIZE) &&
                   m_coordinates.y == 17 * TILE_SIZE) {
            m_coordinates.x = 1 * TILE_SIZE;
        }
    }
}

void GameCharacter::setDirection(direction dir) {
    m_direction = dir;
}

void GameCharacter::collisionHandling(Map &map) {
    for (Obstacle o : map.map) {
        if (isColliding(m_coordinates, o.getCoordinates())) {
            if (o.getTileValue() == 3) { //Vanrette
                if (m_direction == direction::DOWN || m_direction == direction::RIGHT || m_direction == direction::LEFT) {
                    m_coordinates.y = o.getCoordinates().y - TILE_SIZE;
                } else if (m_direction == direction::UP) {
                    m_coordinates.y = o.getCoordinates().y + TILE_SIZE;
                }
            }

            if (o.getTileValue() == 4 || o.getTileValue() == 5) {//Lodrette
                if (m_direction == direction::LEFT) {
                    m_coordinates.x = o.getCoordinates().x + TILE_SIZE;
                } else if (m_direction == direction::RIGHT) {
                    m_coordinates.x = o.getCoordinates().x - TILE_SIZE;
                }
            }

            if (o.getTileValue() == 1 || o.getTileValue() == 11) {//Top-Venstre hjørne
                if (m_direction == direction::DOWN || m_direction == direction::RIGHT) {
                    m_coordinates.x = o.getCoordinates().x - TILE_SIZE;
                    m_coordinates.y = o.getCoordinates().y - TILE_SIZE;
                }
            }

            if (o.getTileValue() == 2 || o.getTileValue() == 12) {//Top-Høyre hjørne
                if (m_direction == direction::DOWN || m_direction == direction::LEFT) {
                    m_coordinates.x = o.getCoordinates().x + TILE_SIZE;
                    m_coordinates.y = o.getCoordinates().y - TILE_SIZE;
                }
            }

            if (o.getTileValue() == 7 || o.getTileValue() == 13) {//Nedre-Venstre hjørne
                if (m_direction == direction::RIGHT || m_direction == direction::UP) {
                    m_coordinates.x = o.getCoordinates().x - TILE_SIZE;
                    m_coordinates.y = o.getCoordinates().y + TILE_SIZE;
                }
            }

            if (o.getTileValue() == 8 || o.getTileValue() == 14) {//Nedre-Høyre hjørne
                if (m_direction == direction::LEFT || m_direction == direction::UP) {
                    m_coordinates.x = o.getCoordinates().x + TILE_SIZE;
                    m_coordinates.y = o.getCoordinates().y + TILE_SIZE;
                }
            }
        }
    }
}

bool GameCharacter::isColliding(SDL_Rect player, SDL_Rect tile) {
    //Checking if any point of player overlaps with any point of the tile.
    return SDL_HasIntersection(&player, &tile);
};

std::vector<bool> GameCharacter::pathAvailable(Map &map) {
    std::vector<bool> pathAvailable = {false, false, false, false};
    // By adding width and height to characters x and y coordinates, we get coordiantes for their center.
    int xCoord = round((m_coordinates.x + (m_coordinates.w / 2)) / TILE_SIZE);
    int yCoord = round((m_coordinates.y + (m_coordinates.h / 2)) / TILE_SIZE);

    for (Obstacle &o : map.map) {
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
            if (o.getTileValue() == 0 || o.getTileValue() == 9 || o.getTileValue() == 10 || o.getTileValue() == 6) {
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

