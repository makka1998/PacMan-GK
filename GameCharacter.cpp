//
// Created by Tobias on 28.03.2020.
//

#include "GameCharacter.h"

GameCharacter::GameCharacter() {
    m_coordinates.x = 6 * 32;
    m_coordinates.y = 9 * 32;
    m_coordinates.h = 13;
    m_coordinates.w = 13;

}

void GameCharacter::checkMovementInput() {
    SDL_PumpEvents();
    if (m_keyStates[SDL_SCANCODE_W] || m_keyStates[SDL_SCANCODE_UP]) {
        m_direction = direction::UP;
    } else if (m_keyStates[SDL_SCANCODE_S] || m_keyStates[SDL_SCANCODE_DOWN]) {
        m_direction = direction::DOWN;
    } else if (m_keyStates[SDL_SCANCODE_D] || m_keyStates[SDL_SCANCODE_RIGHT]) {
        m_direction = direction::RIGHT;
    } else if (m_keyStates[SDL_SCANCODE_A] || m_keyStates[SDL_SCANCODE_LEFT]) {
        m_direction = direction::LEFT;
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
    testTall++;
    if(testTall >=5) {
        testTall = 1;
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


    int tileInfrontValue;
    int tileBehindValue;
    int tileLeftValue;
    int tileRightValue;

/*
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
    return player.x < tile.x + tile.w && player.x + player.w > tile.x && player.y < tile.y + tile.h &&
           player.y + player.h > tile.y;
};

bool GameCharacter::pathAvailable(Map * map){
    int xCoord16th = m_coordinates.x / 16;
    int yCoord16th = m_coordinates.y / 16;
    bool pathAvailable = false;
    int xCoord = m_coordinates.x;
    int yCoord = m_coordinates.y;
    for (Obstacle o : map->map) {
        if (xCoord16th + 1 == o.getCoordinates().x / 16 && yCoord16th == o.getCoordinates().y / 16) {
            if(o.getTileValue() == 0 || o.getTileValue() == 9 || o.getTileValue() == 10){
                std::cout << "HØYRE" << std::endl;
                pathAvailable = true;
            }
        }
        if (xCoord16th - 1 == o.getCoordinates().x / 16 && yCoord16th == o.getCoordinates().y / 16) {
            if(o.getTileValue() == 0 || o.getTileValue() == 9 || o.getTileValue() == 10){
                std::cout << "VENSTRE" << std::endl;
                pathAvailable = true;
            }
        }
        if (xCoord16th == o.getCoordinates().x / 16 && yCoord16th + 1 == o.getCoordinates().y / 16) {
            if(o.getTileValue() == 0 || o.getTileValue() == 9 || o.getTileValue() == 10){
                std::cout << "NED" << std::endl;
                pathAvailable = true;
            }
        }
        if (xCoord16th == o.getCoordinates().x / 16 && yCoord16th - 1 == o.getCoordinates().y / 16) {
            if(o.getTileValue() == 0 || o.getTileValue() == 9 || o.getTileValue() == 10){
                std::cout << "OPP" << std::endl;
                pathAvailable = true;
            }
        }
    }
    return pathAvailable;
}

void GameCharacter::renderCharacter(SDL_Rect srect []) {
    m_texture = IMG_LoadTexture(GameManager::renderer, "../Resources/PacManSpriteSheet.png");

    if (testTall == 1) {
        srect[0].x = 20;
        srect[0].y = 20;
        srect[0].h = 20;
        srect[0].w = 20;
        std::cout << "1: " << std::endl;
    } else if (testTall == 2) {
        srect[1].x =  0;
        srect[1].y = 20;
        srect[1].h = 20;
        srect[1].w = 20;
        std::cout << "2: " << std::endl;
    } else if (testTall == 3) {
        srect[2].x = 40;
        srect[2].y =  0;
        srect[2].h = 20;
        srect[2].w = 20;
        std::cout << "3: " << std::endl;
    } else if (testTall == 4) {
        srect[3].x =  0;
        srect[3].y = 20;
        srect[3].h = 20;
        srect[3].w = 20;
        std::cout << "4: " << std::endl;
    }
    SDL_RenderCopyEx(GameManager::renderer, m_texture, &srect[testTall-1], &m_coordinates, angle, &center, SDL_FLIP_NONE);
}
//    for(int i = 0; i < 4; i++){
//        if(i == 0){
//            srect[0].x = 0;
//            srect[0].y = 0;
//            srect[0].h = 205;
//            srect[0].w = 64;
//            std::cout << "1: " << std::endl;
//        } else if(i == 1){
//            srect[1].x = 64;
//            srect[1].y = 0;
//            srect[1].h = 205;
//            srect[1].w = 64;
//            std::cout << "2: " << std::endl;
//        } else if(i == 2){
//            srect[2].x = 128;
//            srect[2].y = 0;
//            srect[2].h = 205;
//            srect[2].w = 64;
//            std::cout << "3: " << std::endl;
//        } else if(i == 3){
//            srect[3].x = 180;
//            srect[3].y = 0;
//            srect[3].h = 205;
//            srect[3].w = 64;
//            std::cout << "4: " << std::endl;
//        }
//        SDL_RenderCopy(GameManager::renderer, m_texture, &srect[i], &m_coordinates);
//    }
//}
