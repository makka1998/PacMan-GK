//
// Created by Tobias on 30.03.2020.
//

#include "Ghost.h"

//Fiks denne constructoren så den ser pen ut
Ghost::Ghost(int x, int y, int wp1, int wp2, int wp3, int wp4, int wp5, int wp6) {
    m_coordinates.x = x * TILE_SIZE;
    m_coordinates.y = y * TILE_SIZE;

    m_coordinates.h = TILE_SIZE;
    m_coordinates.w = TILE_SIZE;

    m_startingPosition[0] = x;
    m_startingPosition[1] = y;

    wayPointsReached  = {false, false, false, false, false, false, false};
    wayPoints = {wp1, wp2, wp3, wp4, wp5, wp6};
    setDistanceToTarget(m_startingPosition);
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
    if (Mix_Playing(1) != 0) {
        //  Denne While loopen fryser spillet på riktig måte men Spøkelset blir ikke med :o -Martin
    } else {
        m_speed = 100 * GameManager::deltaTime;
        //m_speed = 3;
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
}
void Ghost::getMovementDirection(Map *map) {



//    if(pathAvailable(map).at(0)){
//        if(m_direction != direction::UP){
//            if(m_last_direction != direction::DOWN){
//                m_last_direction = m_direction;
//                m_direction = direction::UP;
//            }
//        }
//        std::cout << "OPP!" << std::endl;
//    }
//    if (pathAvailable(map).at(3)){
//        if(m_direction != direction::RIGHT){
//            if(m_last_direction != direction::LEFT){
//                m_last_direction = m_direction;
//                m_direction = direction::RIGHT;
//            }
//        }
//        std::cout << "HØYRE!" << std::endl;
//    }
//    if (pathAvailable(map).at(1)){
//        if(m_direction != direction::DOWN){
//            if( m_last_direction != direction::UP){
//                m_last_direction = m_direction;
//                m_direction = direction::DOWN;
//            }
//        }
//        std::cout << "NED!" << std::endl;
//    }
//    if (pathAvailable(map).at(2)){
//        if(m_direction != direction::LEFT){
//            if(m_last_direction != direction::RIGHT){
//                m_last_direction = m_direction;
//                m_direction = direction::LEFT;
//            }
//        }
//        std::cout << "VENSTRE!" << std::endl;
//    }


//    if(pathAvailable(map).at(0)){
//        if(m_direction != direction::UP){
//            m_last_direction = m_direction;
//            m_direction = direction::UP;
//        }
//    } else if (pathAvailable(map).at(1)){
//        if(m_direction != direction::DOWN){
//            m_last_direction = m_direction;
//            m_direction = direction::DOWN;
//        }
//    } else if(pathAvailable(map).at(2)){
//        if(m_direction != direction::LEFT){
//            m_last_direction = m_direction;
//            m_direction = direction::LEFT;
//        }
//    } else if(pathAvailable(map).at(3)) {
//        if(m_direction != direction::RIGHT){
//            m_last_direction = m_direction;
//            m_direction = direction::RIGHT;
//        }
//    }

//    //Checking which axis has the most amount of movement, making sure we dont have negative values by multiplying it with itself.
//    if((m_distanceToTarget[0] * m_distanceToTarget[0]) > (m_distanceToTarget[1] * m_distanceToTarget[1])){
//        if (pathAvailable(map).at(2) && m_distanceToTarget[0] < 0){
//            if(m_direction != direction::LEFT){
//                m_last_direction = m_direction;
//                m_direction = direction::LEFT;
//            }
//        } else if (pathAvailable(map).at(3) && m_distanceToTarget[0] > 0){
//            if(m_direction != direction::RIGHT){
//                m_last_direction = m_direction;
//                m_direction = direction::RIGHT;
//            }
//        } else {
//            if(pathAvailable(map).at(0)){
//                if(m_direction != direction::UP){
//                    if(m_last_direction != direction::DOWN){
//                        m_last_direction = m_direction;
//                        m_direction = direction::UP;
//                    }
//                }
//            }else if(pathAvailable(map).at(1)){
//                if(m_direction != direction::DOWN){
//                    if(m_last_direction != direction::UP){
//                        m_last_direction = m_direction;
//                        m_direction = direction::DOWN;
//                    }
//                }
//            }
//            std::cout << "stuck x akse" << std::endl;
//        }
//       // std::cout << "X:" << m_distanceToTarget[0] << std::endl;
//    } else if ((m_distanceToTarget[0] * m_distanceToTarget[0]) < (m_distanceToTarget[1] * m_distanceToTarget[1])) {
//        if (pathAvailable(map).at(0) && m_distanceToTarget[1] < 0){
//            if(m_direction != direction::UP){
//                m_last_direction = m_direction;
//                m_direction = direction::UP;
//            }
//        } else if (pathAvailable(map).at(1) && m_distanceToTarget[1] > 0) {
//            if(m_direction != direction::DOWN){
//                m_last_direction = m_direction;
//                m_direction = direction::DOWN;
//            }
//        } else {
//            if(pathAvailable(map).at(3)){ //Hvis lastDir var opp || ned && !(lastDir == LEFT)
//                if(m_direction != direction::RIGHT){
//                    if(m_last_direction != direction::LEFT){
//                        m_last_direction = m_direction;
//                        m_direction = direction::RIGHT;
//                    }
//                }
//            } else if(pathAvailable(map).at(2)){ //Hvis lastDir var opp || ned && !(lastDir == RIGHT)
//                if(m_direction != direction::LEFT){
//                    if(m_last_direction != direction::RIGHT){
//                        m_last_direction = m_direction;
//                        m_direction = direction::LEFT;
//                    }
//                }
//            }
//            std::cout << "stuck y akse" << std::endl;
//        }
//       // std::cout << "Y: " << m_distanceToTarget[1] << std::endl;
//       }









//    else {
//        if (pathAvailable(map).at(2) && m_distanceToTarget[0] < 0){
//            m_direction = direction::LEFT;
//        } else if (pathAvailable(map).at(0) && m_distanceToTarget[1] < 0) {
//            m_direction = direction::UP;
//        }
//    }


//    if(pathAvailable(map).at(0)){
//        if(m_direction != direction::UP){
//            if(m_last_direction != direction::DOWN){
//                m_last_direction = m_direction;
//                m_direction = direction::UP;
//            }
//        }
//        std::cout << "OPP!" << std::endl;
//    }
//    if (pathAvailable(map).at(3)){
//        if(m_direction != direction::RIGHT){
//            if(m_last_direction != direction::LEFT){
//                m_last_direction = m_direction;
//                m_direction = direction::RIGHT;
//            }
//        }
//        std::cout << "HØYRE!" << std::endl;
//    }
//    if (pathAvailable(map).at(1)){
//        if(m_direction != direction::DOWN){
//            if( m_last_direction != direction::UP){
//                m_last_direction = m_direction;
//                m_direction = direction::DOWN;
//            }
//        }
//        std::cout << "NED!" << std::endl;
//    }
//    if (pathAvailable(map).at(2)){
//        if(m_direction != direction::LEFT){
//            if(m_last_direction != direction::RIGHT){
//                m_last_direction = m_direction;
//                m_direction = direction::LEFT;
//            }
//        }
//        std::cout << "VENSTRE!" << std::endl;
//    }


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
    } else {
        m_direction = direction::RIGHT;
        std::cout << "left 1.2" << std::endl;
    }
    if (pathAvailable(map).at(3) && m_distanceToTarget[0] > 0){
        m_direction = direction::RIGHT;
    } else {
        m_direction = direction::LEFT;
        std::cout << "right 1.2" << std::endl;
    }
    if (pathAvailable(map).at(0) && m_distanceToTarget[1] < 0){
        m_direction = direction::UP;
    } else{
        m_direction = direction::DOWN;
        std::cout << "up 1.2" << std::endl;
    }
    if (pathAvailable(map).at(1) && m_distanceToTarget[1] > 0) {
        m_direction = direction::DOWN;
    } else {
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

void Ghost::setDistanceToTarget(int startingDest []) {
    m_distanceToTarget[0] = startingDest[0] - m_coordinates.x / TILE_SIZE;
    m_distanceToTarget[1] = startingDest[1] - m_coordinates.y / TILE_SIZE;
}

int *  Ghost::getStartingPosition(){
    return m_startingPosition;
}

void Ghost::isCollidingWithPacman(Pacman & pMan){
     if (SDL_HasIntersection(&m_coordinates, pMan.getCoords()) && pMan.getPowerUpDuration() < 5) {
         m_coordinates.x = m_startingPosition[0] * TILE_SIZE;
         m_coordinates.y = m_startingPosition[1] * TILE_SIZE;
         m_startingDestinationReached = false;
         for(auto && wp : wayPointsReached){
             wp = false;
         }
     } else if(SDL_HasIntersection(&m_coordinates, pMan.getCoords())){
         std::cout << pMan.getHealth() << std::endl;
         pMan.setHealth();
         if(pMan.getDirection() == direction::UP){
             pMan.getCoords()->y += TILE_SIZE * 2;
             pMan.setDirection(direction::DOWN);
         }  else if (pMan.getDirection() == direction::DOWN){
             pMan.getCoords()->y -= TILE_SIZE * 2;
             pMan.setDirection(direction::UP);
         } else if (pMan.getDirection() == direction::LEFT){
             pMan.getCoords()->x += TILE_SIZE * 2;
             pMan.setDirection(direction::RIGHT);
         } else if (pMan.getDirection() == direction::RIGHT){
             pMan.getCoords()->x -= TILE_SIZE * 2;
             pMan.setDirection(direction::LEFT);
         }
    }
}

void Ghost::renderCharacter() {

}
