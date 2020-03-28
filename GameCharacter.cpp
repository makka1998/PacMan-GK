//
// Created by Tobias on 28.03.2020.
//

#include "GameCharacter.h"
#include "Pacman.h"

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
}

void GameCharacter::moveCharacter(Map * map) {
    int speed = 2;
    if (m_keyStates[SDL_SCANCODE_TAB]) {
        speed = 4;
    }

    if (m_direction == direction::RIGHT) {
        m_coordinates.x += speed;
        m_texture = IMG_LoadTexture(GameManager::renderer, "../Resources/Real_Pacman_RIGHT.png");
    } else if (m_direction == direction::LEFT) {
        m_coordinates.x += -speed;
        m_texture = IMG_LoadTexture(GameManager::renderer, "../Resources/Real_Pacman_LEFT.png");
    } else if (m_direction == direction::UP) {
        m_coordinates.y += -speed;
        m_texture = IMG_LoadTexture(GameManager::renderer, "../Resources/Real_Pacman_UP.png");
    } else if (m_direction == direction::DOWN) {
        m_coordinates.y += speed;
        m_texture = IMG_LoadTexture(GameManager::renderer, "../Resources/Real_Pacman_DOWN.png");
    } else if(m_direction == direction::NONE) {
        m_texture = IMG_LoadTexture(GameManager::renderer, "../Resources/Real_Pacman_UP.png");
    }

    int PxCoord16th = m_coordinates.x / 16;
    int PyCoord16th = m_coordinates.y / 16;

    int MxCoord16th = m_coordinates.x / 16;
    int Mycoord16th = m_coordinates.y / 16;

    for(Obstacle o : map->map){
        if(PxCoord16th == o.getCoordinates().x / 16 && PyCoord16th == o.getCoordinates().y){
            MxCoord16th = o.getCoordinates().x / 16;
            Mycoord16th = o.getCoordinates().y / 16;
        }
    }



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

void GameCharacter::collisionHandling(Map * map) {
    int pushBackDistance = 2;
    for (Obstacle o : map->map) {

        if (isColliding(m_coordinates, o.getCoordinates())) {
            if (o.getTileValue() == 3) { //Vanrette
                if (m_direction == direction::DOWN) {
                    m_coordinates.y -= pushBackDistance;
                } else if (m_direction == direction::UP) {
                    m_coordinates.y += pushBackDistance;
                }
            }

            if (o.getTileValue() == 4 || o.getTileValue() == 5) {//Lodrette
                if (m_direction == direction::LEFT) {
                    m_coordinates.x += pushBackDistance;
                } else if (m_direction == direction::RIGHT) {
                    m_coordinates.x -= pushBackDistance;
                }
            }

            if (o.getTileValue() == 1 || o.getTileValue() == 11) {//Top-Venstre hjørne
                if (m_direction == direction::DOWN) {
                    m_coordinates.y -= pushBackDistance;
                } else if (m_direction == direction::RIGHT) {
                    m_coordinates.x -= pushBackDistance;
                }
            }

            if (o.getTileValue() == 2 || o.getTileValue() == 12) {//Top-Høyre hjørne
                if (m_direction == direction::DOWN) {
                    m_coordinates.y -= pushBackDistance;
                } else if (m_direction== direction::LEFT) {
                    m_coordinates.x += pushBackDistance;
                }
            }

            if (o.getTileValue() == 7 || o.getTileValue() == 13) {//Nedre-Venstre hjørne
                if (m_direction == direction::RIGHT) {
                    m_coordinates.x -= pushBackDistance;
                } else if (m_direction == direction::UP) {
                    m_coordinates.y += pushBackDistance;
                }
            }

            if (o.getTileValue() == 8 || o.getTileValue() == 14) {//Nedre-Høyre hjørne
                if (m_direction == direction::LEFT) {
                    m_coordinates.x += pushBackDistance;
                } else if (m_direction == direction::UP) {
                    m_coordinates.y += pushBackDistance;
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

void GameCharacter::renderCharacter(){

    SDL_RenderCopy(GameManager::renderer, m_texture, nullptr, &m_coordinates);
}