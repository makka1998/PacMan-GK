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

void GameCharacter::checkMovementInput(Map & map) {
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


void GameCharacter::moveCharacter(Map &map) {
        if (Mix_Playing(-1) != 0  && Mix_Playing(1) == 0) {}
        else {
            m_speed = 200 * GameManager::deltaTime;
            m_animationNumber++;
            if (m_animationNumber >= 13) {
                m_animationNumber = 1;
            }
            if (m_keyStates[SDL_SCANCODE_TAB]) {
                m_speed = 4;
            }

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
            }

            if (m_coordinates.x < 2 && m_coordinates.y == 17 * TILE_SIZE) {
                m_coordinates.x = 29 * TILE_SIZE;
            } else if ((m_coordinates.x < 30.5 * TILE_SIZE && m_coordinates.x > 29.5 * TILE_SIZE) && m_coordinates.y == 17 * TILE_SIZE) {
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
                if (m_direction == direction::DOWN ) {
                    m_coordinates.y = o.getCoordinates().y - TILE_SIZE;
                } else if (m_direction == direction::UP ) {
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
                if (m_direction == direction::DOWN || m_last_direction == direction::UP) {
                    m_coordinates.y = o.getCoordinates().y - TILE_SIZE;
                    m_coordinates.x = o.getCoordinates().x - TILE_SIZE;
                } else if (m_direction == direction::RIGHT || m_last_direction == direction::LEFT) {
                    m_coordinates.x = o.getCoordinates().x - TILE_SIZE;
                    m_coordinates.y = o.getCoordinates().y - TILE_SIZE;
                }
            }

            if (o.getTileValue() == 2 || o.getTileValue() == 12) {//Top-Høyre hjørne
                if (m_direction == direction::DOWN || m_last_direction == direction::UP) {
                    m_coordinates.y = o.getCoordinates().y - TILE_SIZE;
                    m_coordinates.x = o.getCoordinates().x + TILE_SIZE;
                } else if (m_direction == direction::LEFT || m_last_direction == direction::RIGHT) {
                    m_coordinates.x = o.getCoordinates().x + TILE_SIZE;
                    m_coordinates.y = o.getCoordinates().y - TILE_SIZE;
                }
            }

            if (o.getTileValue() == 7 || o.getTileValue() == 13) {//Nedre-Venstre hjørne
                if (m_direction == direction::RIGHT|| m_last_direction == direction::LEFT) {
                    m_coordinates.x = o.getCoordinates().x - TILE_SIZE;
                    m_coordinates.y = o.getCoordinates().y + TILE_SIZE;
                } else if (m_direction == direction::UP  || m_last_direction == direction::DOWN) {
                    m_coordinates.y = o.getCoordinates().y + TILE_SIZE;
                    m_coordinates.x = o.getCoordinates().x - TILE_SIZE;
                }
            }

            if (o.getTileValue() == 8 || o.getTileValue() == 14) {//Nedre-Høyre hjørne
                if (m_direction == direction::LEFT  || m_direction == direction::RIGHT || m_last_direction == direction::RIGHT ) {
                    m_coordinates.x = o.getCoordinates().x + TILE_SIZE;
                    m_coordinates.y = o.getCoordinates().y + TILE_SIZE;
                } else if (m_direction == direction::UP  || m_last_direction == direction::DOWN) {
                    m_coordinates.y = o.getCoordinates().y + TILE_SIZE;
                    m_coordinates.x = o.getCoordinates().x + TILE_SIZE;
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

void GameCharacter::renderCharacter(SDL_Rect srect[]) {
    SDL_RenderCopyEx(GameManager::renderer, m_texture, &srect[m_animationNumber - 1], &m_coordinates, angle, &center,
                     SDL_FLIP_NONE);
}
