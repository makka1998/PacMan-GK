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

void GameCharacter::checkMovementInput(Map * map) {
    SDL_PumpEvents();
    if (Mix_Playing(1) != 0) {
    } else {
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
}

//    if (m_direction == direction::UP && m_last_direction == direction::DOWN) {
//        //Tillat endring, det er på samme akse.
//        m_direction = direction::UP;
//    } else if (m_direction == direction::DOWN && m_last_direction == direction::UP) {
//        //Tillat endring, det er på samme akse.
//        m_direction = direction::DOWN;
//    } else if (m_direction == direction::LEFT && m_last_direction == direction::RIGHT) {
//        //Tillat endring, det er på samme akse.
//        m_direction = direction::LEFT;
//    } else if (m_direction == direction::RIGHT && m_last_direction == direction::LEFT) {
//        //Tillat endring, det er på samme akse.
//        m_direction = direction::RIGHT;
//
//    } else if ((m_direction == direction::RIGHT || m_direction == direction::LEFT) && (m_last_direction == direction::DOWN || m_last_direction == direction::UP)) {
//        if (m_direction == direction::RIGHT) {
//            if(pathAvailable(map).at(3)){
//                m_direction = direction::RIGHT;
//            }
//
//        } else if (m_direction == direction::LEFT) {
//            if(pathAvailable(map).at(2)){
//                m_direction = direction::LEFT;
//            }
//        }
//    } else if ((m_direction == direction::UP || m_direction == direction::DOWN) && (m_last_direction == direction::LEFT || m_last_direction == direction::RIGHT)) {
//        if (m_direction == direction::UP) {
//            for (Obstacle o : map->map) {
//                if (xCoord16th == o.getCoordinates().x / 16 && yCoord16th - 1 == o.getCoordinates().y / 16) {
//                    m_coordinates.y += -m_speed;
//                }
//            }
//        } else if (m_direction == direction::DOWN) {
//            for (Obstacle o : map->map) {
//                if (xCoord16th == o.getCoordinates().x / 16 && yCoord16th + 1 == o.getCoordinates().y / 16) {
//                    m_coordinates.y += m_speed;
//                }
//            }
//        }
//    }



//    if (m_keyStates[SDL_SCANCODE_W] && !(m_last_keyStates[SDL_SCANCODE_W])) {
//        m_direction = direction::UP;
//    } else if (m_keyStates[SDL_SCANCODE_S] && !(m_last_keyStates[SDL_SCANCODE_S])) {
//        m_direction = direction::DOWN;
//    } else if (m_keyStates[SDL_SCANCODE_D] && !(m_last_keyStates[SDL_SCANCODE_D])) {
//        m_direction = direction::RIGHT;
//    } else if (m_keyStates[SDL_SCANCODE_A] && !(m_last_keyStates[SDL_SCANCODE_A])) {
//        m_direction = direction::LEFT;
//    }
//
//    std::cout << "Current: " << (int)m_keyStates[SDL_SCANCODE_W] << (int)m_keyStates[SDL_SCANCODE_A] << (int)m_keyStates[SDL_SCANCODE_S] << (int)m_keyStates[SDL_SCANCODE_D] << std::endl;
//    //std::cout << " Last: "<< (int)m_last_keyStates[SDL_SCANCODE_W] << (int)m_last_keyStates[SDL_SCANCODE_A] << (int)m_last_keyStates[SDL_SCANCODE_S] << (int)m_last_keyStates[SDL_SCANCODE_D] << std::endl;
//    m_last_keyStates = m_keyStates;


void GameCharacter::moveCharacter(Map *map) {

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
        } else if ((m_coordinates.x < 30.5 * TILE_SIZE && m_coordinates.x > 29.5 * TILE_SIZE) &&
                   m_coordinates.y == 17 * TILE_SIZE) {
            m_coordinates.x = 1 * TILE_SIZE;
        }
    }


    /*  Sjekker om tiles rundt pacman er hindring.
    int playerGridCord_X = round((m_coordinates.x + (m_coordinates.w) / 2) / TILE_SIZE);
    int playerGridCord_Y = round((m_coordinates.y + (m_coordinates.h) / 2) / TILE_SIZE);

    int Players_LeftTile = playerGridCord_X - 1;
    int Players_RightTile = playerGridCord_X + 1;
    int Players_UpTile = playerGridCord_Y - 1;
    int Players_DownTile = playerGridCord_Y + 1;

    for (Obstacle tile : map->map) {
        int tileGridCord_X = tile.getCoordinates().x / TILE_SIZE;
        int tileGridCord_Y = tile.getCoordinates().y / TILE_SIZE;
        if (tile.getTileValue() != 10 && tile.getTileValue() != 9 && tile.getTileValue() != 6 && tile.getTileValue() != 0){
            if (tileGridCord_X == Players_LeftTile && tileGridCord_Y == playerGridCord_Y) {     //LEFT
                //Direction LEFT not allowed
            } else if (tileGridCord_X == Players_RightTile && tileGridCord_Y == playerGridCord_Y) {  //RIGHT
                //Direction RIGHT not allowed

            } else if (tileGridCord_X == playerGridCord_X && tileGridCord_Y == Players_UpTile) {    //UP
                //Direction UP not allowed

            } else if (tileGridCord_X == playerGridCord_X && tileGridCord_Y == Players_DownTile) {  //DOWN
                //Direction DOWN not allowed

            }
        }
    }
     */

/*

    int tileInfrontValue;
    int tileBehindValue;
    int tileLeftValue;
    int tileRightValue;


    if(m_direction == direction::LEFT){
        std::cout << "DIR= LEFT" << std::endl;
    }else if(m_direction == direction::RIGHT){
        std::cout << "DIR= RIGHTH" << std::endl;
    } else if(m_direction == direction::UP){
        std::cout << "DIR= UP" << std::endl;
    } else if(m_direction == direction::DOWN){
        std::cout << "DIR= dOWN" << std::endl;
    }

    if(m_last_direction == direction::LEFT){
        std::cout << "LAST DIR= LEFT" << std::endl;
    }else if(m_last_direction == direction::RIGHT){
        std::cout << "LAST DIR= RIGHTH" << std::endl;
    } else if(m_last_direction == direction::UP){
        std::cout << "LAST DIR= UP" << std::endl;
    } else if(m_last_direction == direction::DOWN){
        std::cout << "LAST DIR= dOWN" << std::endl;
    }
*/

    //int xCoord16th = m_coordinates.x / TILE_SIZE; xxx im triple X rated
    //int yCoord16th = m_coordinates.y / TILE_SIZE; xxx im triple X rated
    //std::cout << "X: " << xCoord16th << " Y: " << yCoord16th << std::endl;
//
//    int MxCoord16th = m_coordinates.x / 16;
//    int Mycoord16th = m_coordinates.y / 16;
//
//    std::vector<int> tileInfront;
//    std::vector<int> tileBehind;
//    std::vector<int> tileLeft;
//    std::vector<int> tileRight;
//
//    for (Obstacle o : map->map) {
//        if (xCoord16th + 1 == o.getCoordinates().x / 16 && yCoord16th == o.getCoordinates().y / 16) {
//            tileRight.emplace_back(o.getCoordinates().x / 16);
//            tileRight.emplace_back(o.getCoordinates().y / 16);
//        }
//        if (xCoord16th - 1 == o.getCoordinates().x / 16 && yCoord16th == o.getCoordinates().y / 16) {
//            tileLeft.emplace_back(o.getCoordinates().x / 16);
//            tileLeft.emplace_back(o.getCoordinates().y / 16);
//        }
//        if (xCoord16th == o.getCoordinates().x / 16 && yCoord16th + 1 == o.getCoordinates().y / 16) {
//            tileBehind.emplace_back(o.getCoordinates().x / 16);
//            tileBehind.emplace_back(o.getCoordinates().y / 16);
//        }
//        if (xCoord16th == o.getCoordinates().x / 16 && yCoord16th - 1 == o.getCoordinates().y / 16) {
//            tileInfront.emplace_back(o.getCoordinates().x / 16);
//            tileInfront.emplace_back(o.getCoordinates().y / 16);
//        }
//    }
//


/*
    if ((o.getTileValue() == 4 || o.getTileValue() == 5) && ) {//Lodrette
        if (m_direction == direction::LEFT) {
            m_coordinates.x += pushBackDistance;
        } else if (m_direction == direction::RIGHT) {
            m_coordinates.x -= pushBackDistance;
        }
    }
    */


//Check out if direction::NONE is making it not work. -Jonas
void GameCharacter::collisionHandling(Map *map) {
    //int pushBackDistance = 10;
    for (Obstacle o : map->map) {
        if (isColliding(m_coordinates, o.getCoordinates())) {
            if (o.getTileValue() == 3) { //Vanrette
                if (m_direction == direction::DOWN) {
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
                if (m_direction == direction::DOWN) {
                    m_coordinates.y = o.getCoordinates().y - TILE_SIZE;
                    m_coordinates.x = o.getCoordinates().x - TILE_SIZE;
                } else if (m_direction == direction::RIGHT) {
                    m_coordinates.x = o.getCoordinates().x - TILE_SIZE;
                    m_coordinates.y = o.getCoordinates().y - TILE_SIZE;
                }
            }

            if (o.getTileValue() == 2 || o.getTileValue() == 12) {//Top-Høyre hjørne
                if (m_direction == direction::DOWN) {
                    m_coordinates.y = o.getCoordinates().y - TILE_SIZE;
                    m_coordinates.x = o.getCoordinates().x + TILE_SIZE;
                } else if (m_direction == direction::LEFT) {
                    m_coordinates.x = o.getCoordinates().x + TILE_SIZE;
                    m_coordinates.y = o.getCoordinates().y - TILE_SIZE;
                }
            }

            if (o.getTileValue() == 7 || o.getTileValue() == 13) {//Nedre-Venstre hjørne
                if (m_direction == direction::RIGHT) {
                    m_coordinates.x = o.getCoordinates().x - TILE_SIZE;
                    m_coordinates.y = o.getCoordinates().y + TILE_SIZE;
                } else if (m_direction == direction::UP) {
                    m_coordinates.y = o.getCoordinates().y + TILE_SIZE;
                    m_coordinates.x = o.getCoordinates().x - TILE_SIZE;
                }
            }

            if (o.getTileValue() == 8 || o.getTileValue() == 14) {//Nedre-Høyre hjørne
                if (m_direction == direction::LEFT) {
                    m_coordinates.x = o.getCoordinates().x + TILE_SIZE;
                    m_coordinates.y = o.getCoordinates().y + TILE_SIZE;
                } else if (m_direction == direction::UP) {
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

std::vector<bool> GameCharacter::pathAvailable(Map *map) {
    std::vector<bool> pathAvailable = {false, false, false, false};
    // By adding width and height to characters x and y coordinates, we get coordiantes for their center.
    int xCoord = round((m_coordinates.x + (m_coordinates.w / 2)) / TILE_SIZE);
    int yCoord = round((m_coordinates.y + (m_coordinates.h / 2)) / TILE_SIZE);

    for (Obstacle o : map->map) {
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
