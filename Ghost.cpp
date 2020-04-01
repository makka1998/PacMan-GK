//
// Created by Tobias on 30.03.2020.
//

#include "Ghost.h"
Ghost::Ghost() {
    m_coordinates.x = 24 * TILE_SIZE;
    m_coordinates.y = 4 * TILE_SIZE;

    m_coordinates.h = TILE_SIZE;
    m_coordinates.w = TILE_SIZE;
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
    m_speed = 250 * GameManager::deltaTime;

    if (m_direction == direction::RIGHT) {
        m_coordinates.x += m_speed;

    } else if (m_direction == direction::LEFT) {
        m_coordinates.x += -m_speed;

    } else if (m_direction == direction::UP) {
        m_coordinates.y += -m_speed;
    } else if (m_direction == direction::DOWN) {
        m_coordinates.y += m_speed;
    }
}

void Ghost::getMovementDirection(Map * map) {
    int directionDecider;
    //Checking which axis has the most amount of movement, making sure we dont have negative values by multiplying it with itself.
    if((m_distanceToTarget[0] * m_distanceToTarget[0]) > (m_distanceToTarget[1] * m_distanceToTarget[1])){
        if (pathAvailable(map).at(2) && m_distanceToTarget[0] < 0){
            m_direction = direction::LEFT;
        } else if (pathAvailable(map).at(3) && m_distanceToTarget[0] > 0){
            m_direction = direction::RIGHT;
        } else {
            if(pathAvailable(map).at(0)){
                m_direction = direction::UP;
                directionDecider = 1;
            }else if(pathAvailable(map).at(1)){
                m_direction = direction::DOWN;
                directionDecider = 2;
            }
            std::cout << "stuck x akse" << std::endl;
        }
       // std::cout << "X:" << m_distanceToTarget[0] << std::endl;
    } else if ((m_distanceToTarget[0] * m_distanceToTarget[0]) < (m_distanceToTarget[1] * m_distanceToTarget[1])) {
        if (pathAvailable(map).at(0) && m_distanceToTarget[1] < 0){
            m_direction = direction::UP;
        } else if (pathAvailable(map).at(1) && m_distanceToTarget[1] > 0) {
            m_direction = direction::DOWN;
        } else {
            if(pathAvailable(map).at(3)){
                m_direction = direction::RIGHT;
            } else if(pathAvailable(map).at(2)){
                m_direction = direction::LEFT;
            }
            std::cout << "stuck y akse" << std::endl;
        }
       // std::cout << "Y: " << m_distanceToTarget[1] << std::endl;
    } else {
        if (pathAvailable(map).at(2) && m_distanceToTarget[0] < 0){
            m_direction = direction::LEFT;
        } else if (pathAvailable(map).at(3) && m_distanceToTarget[0] > 0) {
            m_direction = direction::RIGHT;
        }
    }



//    if (pathAvailable(map).at(2) && m_distanceToTarget[0] < 0){
//        m_direction = direction::LEFT;
//    }
//    if (pathAvailable(map).at(3) && m_distanceToTarget[0] > 0){
//
//        m_direction = direction::RIGHT;
//    }
//    if (pathAvailable(map).at(0) && m_distanceToTarget[1] < 0){
//        m_direction = direction::UP;
//    }
//    if (pathAvailable(map).at(1) && m_distanceToTarget[1] > 0) {
//        m_direction = direction::DOWN;
//    }

//    if(("Er til venstre"){
//        if(!(pathAvailable(map).at(2))){
//            //m_direction = direction::UP;
//            //m_direction = direction::DOWN;
//        }else{
//            m_direction = direction::LEFT;
//        }
//    }

    /*
     if (pathAvailable(map).at(2) && m_distanceToTarget[0] < 0){ // Er det mulig å dra til venstre og er pacman til venstre for meg?
        m_direction = direction::LEFT; // Dra til venstre
    } else if (){
        m_direction = direction::RIGHT;
        std::cout << "left 1.2" << std::endl;
    }
    if (pathAvailable(map).at(3) && m_distanceToTarget[0] > 0){
        m_direction = direction::RIGHT;
    } else if (){
        m_direction = direction::LEFT;
        std::cout << "right 1.2" << std::endl;
    }
    if (pathAvailable(map).at(0) && m_distanceToTarget[1] < 0){
        m_direction = direction::UP;
    } else if (){
        m_direction = direction::DOWN;
        std::cout << "up 1.2" << std::endl;
    }
    if (pathAvailable(map).at(1) && m_distanceToTarget[1] > 0) {
        m_direction = direction::DOWN;
    } else if (){
        m_direction = direction::UP;
        std::cout << "down 1.2" << std::endl;
    }
     */

    /*
     if(distanceToTarget[0] != 0){
        if(distanceToTarget[0] < 0){
            m_direction = direction::LEFT;
        } else {
            m_direction = direction::RIGHT;
        }
    } else if(distanceToTarget[1] != 0){
        if(distanceToTarget[1] < 0){
            m_direction = direction::UP;
        } else {
            m_direction = direction::DOWN;
        }
    }
     */

    /*
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

     */
}

void Ghost::setDistanceToTarget(SDL_Rect pacmanPos) {
    m_distanceToTarget[0] = pacmanPos.x - m_coordinates.x;
    m_distanceToTarget[1] = pacmanPos.y - m_coordinates.y;
    m_pacmanPos = pacmanPos;
}

void Ghost::renderCharacter() {
    m_texture = IMG_LoadTexture(GameManager::renderer, "../Resources/Old_Tilesets/PacManSpriteSheet_20x20.png");
    SDL_Rect srect;
    srect.y = 4 * TILE_SIZE;
    srect.x = 0;
    srect.h = TILE_SIZE;
    srect.w = TILE_SIZE;
    SDL_RenderCopy(GameManager::renderer, m_texture, &srect, &m_coordinates);
}
