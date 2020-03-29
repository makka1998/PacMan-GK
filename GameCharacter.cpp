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

void GameCharacter::checkMovementInput() {
    SDL_PumpEvents();
    if (m_keyStates[SDL_SCANCODE_W] || m_keyStates[SDL_SCANCODE_UP]) {
        if (m_direction != direction::UP) {
            m_last_direction = m_direction;
            m_direction = direction::UP;
        }
    } else if (m_keyStates[SDL_SCANCODE_S] || m_keyStates[SDL_SCANCODE_DOWN]) {
        if (m_direction != direction::DOWN) {
            m_last_direction = m_direction;
            m_direction = direction::DOWN;
        }
    } else if (m_keyStates[SDL_SCANCODE_D] || m_keyStates[SDL_SCANCODE_RIGHT]) {
        if (m_direction != direction::RIGHT) {
            m_last_direction = m_direction;
            m_direction = direction::RIGHT;
        }
    } else if (m_keyStates[SDL_SCANCODE_A] || m_keyStates[SDL_SCANCODE_LEFT]) {
        if (m_direction != direction::LEFT) {
            m_last_direction = m_direction;
            m_direction = direction::LEFT;
        }
    }

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
}

void GameCharacter::moveCharacter(Map *map) {
    int speed = 2;

    animationNumber++;
    if (animationNumber >= 13) {
        animationNumber = 1;
    }
    if (m_keyStates[SDL_SCANCODE_TAB]) {
        speed = 4;
    }

    if (m_direction == direction::RIGHT) {
        m_coordinates.x += speed;
        angle = 0;

    } else if (m_direction == direction::LEFT) {
        m_coordinates.x += -speed;
        angle = 180;

    } else if (m_direction == direction::UP) {
        m_coordinates.y += -speed;
        angle = -90;

    } else if (m_direction == direction::DOWN) {
        m_coordinates.y += speed;
        angle = 90;
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

//    int xCoord16th = m_coordinates.x / 16;
//    int yCoord16th = m_coordinates.y / 16;
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
//    if (m_direction == m_last_direction) {
//        //Fortsett som før
//        if(m_direction == direction::UP){
//            m_coordinates.y += -speed;
//            m_texture = IMG_LoadTexture(GameManager::renderer, "../Resources/Real_Pacman_UP.png");
//        } else if (m_direction == direction::DOWN){
//            m_coordinates.y += speed;
//            m_texture = IMG_LoadTexture(GameManager::renderer, "../Resources/Real_Pacman_DOWN.png");
//        } else if (m_direction == direction::LEFT){
//            m_coordinates.x += -speed;
//            m_texture = IMG_LoadTexture(GameManager::renderer, "../Resources/Real_Pacman_LEFT.png");
//        } else if (m_direction == direction::RIGHT){
//            m_coordinates.x += speed;
//            m_texture = IMG_LoadTexture(GameManager::renderer, "../Resources/Real_Pacman_RIGHT.png");
//        }
//    } else {
//        if (m_direction == direction::UP && m_last_direction == direction::DOWN) {
//            //Tillat endring, det er på samme akse.
//            m_coordinates.y += -speed;
//            m_texture = IMG_LoadTexture(GameManager::renderer, "../Resources/Real_Pacman_UP.png");
//        } else if (m_direction == direction::DOWN && m_last_direction == direction::UP) {
//            //Tillat endring, det er på samme akse.
//            m_coordinates.y += speed;
//            m_texture = IMG_LoadTexture(GameManager::renderer, "../Resources/Real_Pacman_DOWN.png");
//        } else if (m_direction == direction::LEFT && m_last_direction == direction::RIGHT) {
//            //Tillat endring, det er på samme akse.
//            m_coordinates.x += -speed;
//            m_texture = IMG_LoadTexture(GameManager::renderer, "../Resources/Real_Pacman_LEFT.png");
//        } else if (m_direction == direction::RIGHT && m_last_direction == direction::LEFT) {
//            //Tillat endring, det er på samme akse.
//            m_coordinates.x += speed;
//            m_texture = IMG_LoadTexture(GameManager::renderer, "../Resources/Real_Pacman_RIGHT.png");
//
//        } else if ((m_direction == direction::RIGHT || m_direction == direction::LEFT) && (m_last_direction == direction::DOWN || m_last_direction == direction::UP)){
//            if(m_direction == direction::RIGHT){
//                for(Obstacle o : map->map){
//                    if (xCoord16th + 1 == o.getCoordinates().x / 16 && yCoord16th == o.getCoordinates().y / 16) {
//                        if(o.getTileValue() == 0 || o.getTileValue() == 9 || o.getTileValue() == 10){
//                            m_coordinates.x += speed;
//                            m_texture = IMG_LoadTexture(GameManager::renderer, "../Resources/Real_Pacman_RIGHT.png");
//                            std::cout << "Her er det egentlig en vegg" << std::endl;
//                        }
//                    }
//                }
//            } else if(m_direction == direction::LEFT){
//                for(Obstacle o : map->map){
//                    if (xCoord16th - 1 == o.getCoordinates().x / 16 && yCoord16th == o.getCoordinates().y / 16) {
//                        if(o.getTileValue() == 0 || o.getTileValue() == 9 || o.getTileValue() == 10){
//                            m_coordinates.x += -speed;
//                            m_texture = IMG_LoadTexture(GameManager::renderer, "../Resources/Real_Pacman_LEFT.png");
//                        }
//                    }
//                }
//            }
//        } else if ((m_direction == direction::UP || m_direction == direction::DOWN) && (m_last_direction == direction::LEFT || m_last_direction == direction::RIGHT)) {
//            if(m_direction == direction::UP){
//                for(Obstacle o : map->map){
//                    if (xCoord16th == o.getCoordinates().x / 16 && yCoord16th - 1 == o.getCoordinates().y / 16) {
//                        m_coordinates.y += -speed;
//                        m_texture = IMG_LoadTexture(GameManager::renderer, "../Resources/Real_Pacman_UP.png");
//                    }
//                }
//            } else if(m_direction == direction::DOWN){
//                for(Obstacle o : map->map){
//                    if (xCoord16th == o.getCoordinates().x / 16 && yCoord16th + 1 == o.getCoordinates().y / 16) {
//                        m_coordinates.y += speed;
//                        m_texture = IMG_LoadTexture(GameManager::renderer, "../Resources/Real_Pacman_DOWN.png");
//                    }
//                }
//            }
//        }
//    }

/*
    if ((o.getTileValue() == 4 || o.getTileValue() == 5) && ) {//Lodrette
        if (m_direction == direction::LEFT) {
            m_coordinates.x += pushBackDistance;
        } else if (m_direction == direction::RIGHT) {
            m_coordinates.x -= pushBackDistance;
        }
    }
    */
}

//Check out if direction::NONE is making it not work. -Jonas
void GameCharacter::collisionHandling(Map *map) {
    int pushBackDistance = 2;
    for (Obstacle o : map->map) {
        if (isColliding(m_coordinates, o.getCoordinates())) {
            if (o.getTileValue() == 3) { //Vanrette
                if (m_direction == direction::DOWN) {
                    m_coordinates.y -= pushBackDistance;
                    m_direction = direction::NONE;
                } else if (m_direction == direction::UP) {
                    m_coordinates.y += pushBackDistance;
                    m_direction = direction::NONE;
                }
            }

            if (o.getTileValue() == 4 || o.getTileValue() == 5) {//Lodrette
                if (m_direction == direction::LEFT) {
                    m_coordinates.x += pushBackDistance;
                    m_direction = direction::NONE;
                } else if (m_direction == direction::RIGHT) {
                    m_coordinates.x -= pushBackDistance;
                    m_direction = direction::NONE;
                }
            }

            if (o.getTileValue() == 1 || o.getTileValue() == 11) {//Top-Venstre hjørne
                if (m_direction == direction::DOWN) {
                    m_coordinates.y -= pushBackDistance;
                    m_direction = direction::NONE;
                } else if (m_direction == direction::RIGHT) {
                    m_coordinates.x -= pushBackDistance;
                    m_direction = direction::NONE;
                }
            }

            if (o.getTileValue() == 2 || o.getTileValue() == 12) {//Top-Høyre hjørne
                if (m_direction == direction::DOWN) {
                    m_coordinates.y -= pushBackDistance;
                    m_direction = direction::NONE;
                } else if (m_direction == direction::LEFT) {
                    m_coordinates.x += pushBackDistance;
                    m_direction = direction::NONE;
                }
            }

            if (o.getTileValue() == 7 || o.getTileValue() == 13) {//Nedre-Venstre hjørne
                if (m_direction == direction::RIGHT) {
                    m_coordinates.x -= pushBackDistance;
                    m_direction = direction::NONE;
                } else if (m_direction == direction::UP) {
                    m_coordinates.y += pushBackDistance;
                    m_direction = direction::NONE;
                }
            }

            if (o.getTileValue() == 8 || o.getTileValue() == 14) {//Nedre-Høyre hjørne
                if (m_direction == direction::LEFT) {
                    m_coordinates.x += pushBackDistance;
                    m_direction = direction::NONE;
                } else if (m_direction == direction::UP) {
                    m_coordinates.y += pushBackDistance;
                    m_direction = direction::NONE;
                }
            }
        }
    }
}

bool GameCharacter::isColliding(SDL_Rect player, SDL_Rect tile) {
    //Checking if any point of player overlaps with any point of the tile.
    return SDL_HasIntersection(&player, &tile);
};

bool GameCharacter::pathAvailable(Map *map) {
    int xCoord16th = m_coordinates.x / 16;
    int yCoord16th = m_coordinates.y / 16;
    bool pathAvailable = false;
    int xCoord = m_coordinates.x;
    int yCoord = m_coordinates.y;
    for (Obstacle o : map->map) {
        if (xCoord16th + 1 == o.getCoordinates().x / 16 && yCoord16th == o.getCoordinates().y / 16) {
            if (o.getTileValue() == 0 || o.getTileValue() == 9 || o.getTileValue() == 10) {
                //std::cout << "HØYRE" << std::endl;
                pathAvailable = true;
            }
        }
        if (xCoord16th - 1 == o.getCoordinates().x / 16 && yCoord16th == o.getCoordinates().y / 16) {
            if (o.getTileValue() == 0 || o.getTileValue() == 9 || o.getTileValue() == 10) {
                //std::cout << "VENSTRE" << std::endl;
                pathAvailable = true;
            }
        }
        if (xCoord16th == o.getCoordinates().x / 16 && yCoord16th + 1 == o.getCoordinates().y / 16) {
            if (o.getTileValue() == 0 || o.getTileValue() == 9 || o.getTileValue() == 10) {
                //std::cout << "NED" << std::endl;
                pathAvailable = true;
            }
        }
        if (xCoord16th == o.getCoordinates().x / 16 && yCoord16th - 1 == o.getCoordinates().y / 16) {
            if (o.getTileValue() == 0 || o.getTileValue() == 9 || o.getTileValue() == 10) {
                //std::cout << "OPP" << std::endl;
                pathAvailable = true;
            }
        }
    }
    return pathAvailable;
}

void GameCharacter::renderCharacter(SDL_Rect srect[]) {
    SDL_RenderCopyEx(GameManager::renderer, m_texture, &srect[animationNumber - 1], &m_coordinates, angle, &center,
                     SDL_FLIP_NONE);
}
