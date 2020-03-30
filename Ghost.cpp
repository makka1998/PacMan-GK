//
// Created by Tobias on 30.03.2020.
//

#include "Ghost.h"
Ghost::Ghost() {
    m_coordinates.x = 26 * TILE_SIZE;
    m_coordinates.y = 18 * TILE_SIZE;

    m_coordinates.h = TILE_SIZE - 0;
    m_coordinates.w = TILE_SIZE - 0;
}

/*
void Ghost::checkMovementInput(Map *map) {
    SDL_PumpEvents();
    if (m_keyStates[SDL_SCANCODE_W] || m_keyStates[SDL_SCANCODE_UP]) {
        if (m_direction != direction::UP) {
            if(pathAvailable(map).at(0)){
                m_last_direction = m_direction;
                m_direction = direction::UP;
            }
        }
    } else if (m_keyStates[SDL_SCANCODE_S] || m_keyStates[SDL_SCANCODE_DOWN]) {
        if (m_direction != direction::DOWN) {
            if(pathAvailable(map).at(1)){
                m_last_direction = m_direction;
                m_direction = direction::DOWN;
            }
        }
    } else if (m_keyStates[SDL_SCANCODE_D] || m_keyStates[SDL_SCANCODE_RIGHT]) {
        if (m_direction != direction::RIGHT) {
            if(pathAvailable(map).at(3)){
                m_last_direction = m_direction;
                m_direction = direction::RIGHT;
            }
        }
    } else if (m_keyStates[SDL_SCANCODE_A] || m_keyStates[SDL_SCANCODE_LEFT]) {
        if (m_direction != direction::LEFT) {
            if(pathAvailable(map).at(2)){
                m_last_direction = m_direction;
                m_direction = direction::LEFT;
            }
        }
    }
}
*/
void Ghost::moveCharacter(Map *map) {
    //Hmm hvis minus på en av aksene så betyr det under eller til høyre, har ikke brain capacity til å regne/tenke det ut
    if(distanceToTarget[0] != 0){
        if(distanceToTarget[0] < 0){
            m_coordinates.x -= speed;
           // distanceToTarget[0] = distanceToTarget[0] + 2 * TILE_SIZE;
        } else if(distanceToTarget[0] > 0){
            m_coordinates.x += speed;
          //  distanceToTarget[0] = distanceToTarget[0] - 2 * TILE_SIZE;
        }
    } else if(distanceToTarget[1] != 0){
        if(distanceToTarget[1] < 0){
            m_coordinates.y -= speed;
           // distanceToTarget[1] = distanceToTarget[1] + 2 * TILE_SIZE;
        } else if(distanceToTarget[1] > 0){
            m_coordinates.y += speed;
          //  distanceToTarget[1] = distanceToTarget[1] - 2 * TILE_SIZE;
        }
    }
    speed += 0.5;
}

void Ghost::setDistanceToTarget(SDL_Rect pacmanPos) {
    distanceToTarget[0] = pacmanPos.x - m_coordinates.x;
    distanceToTarget[1] = pacmanPos.y - m_coordinates.y;
}

void Ghost::renderCharacter() {
    SDL_Rect srect;
    srect.y = 4 * TILE_SIZE;
    srect.x = 0;
    srect.h = 1.2 * TILE_SIZE;
    srect.w = TILE_SIZE;
    m_texture = IMG_LoadTexture(GameManager::renderer, "../Resources/Old_Tilesets/PacManSpriteSheet_20x20.png");
SDL_RenderCopy(GameManager::renderer, m_texture, &srect, &m_coordinates);
}
