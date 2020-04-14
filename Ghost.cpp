#include "Ghost.h"

//Fiks denne constructoren så den ser pen ut
Ghost::Ghost(int xs, int ys, int xr, int yr, int wp1, int wp2, int wp3, int wp4, int wp5, int wp6) {
    m_coordinates.x = xs * TILE_SIZE;
    m_coordinates.y = ys * TILE_SIZE;

    m_coordinates.h = TILE_SIZE;
    m_coordinates.w = TILE_SIZE;

    m_startingPosition[0] = xs;
    m_startingPosition[1] = ys;

    m_respawnPosition[0] = xr;
    m_respawnPosition[1] = yr;
    wayPointsReached  = {false, false, false, false, false, false, false};
    wayPoints = {wp1, wp2, wp3, wp4, wp5, wp6};
    setDistanceToTarget(m_startingPosition);
}

void Ghost::moveCharacter(Map &map) {
    if (Mix_Playing(1) != 0) {
        //  Denne While loopen fryser spillet på riktig måte men Spøkelset blir ikke med :o -Martin
    } else {
            m_speed = 140 * GameManager::deltaTime;
        //m_speed = 1;
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
void Ghost::getMovementDirection(Map &map) {


}

void Ghost::setDistanceToTarget(int startingDest []) {
    m_distanceToTarget[0] = startingDest[0] - m_coordinates.x / TILE_SIZE;
    m_distanceToTarget[1] = startingDest[1] - m_coordinates.y / TILE_SIZE;
}

int *  Ghost::getStartingPosition(){
    return m_startingPosition;
}

void Ghost::isCollidingWithPacman(Pacman & pMan, const std::vector<std::shared_ptr<Ghost>>& gameCharacters){
     if (SDL_HasIntersection(&m_coordinates, pMan.getCoords()) && pMan.getPowerUpDuration() < 5) {
         m_coordinates.x = m_respawnPosition[0] * TILE_SIZE;
         m_coordinates.y = m_respawnPosition[1] * TILE_SIZE;
     } else if(SDL_HasIntersection(&m_coordinates, pMan.getCoords())){
         pMan.setHealth();
         pMan.startPos();

         //ghost's Reset:
         for (const auto& ghost : gameCharacters){
                ghost->moveRespawnPos();
         }
    }
}

void Ghost::renderCharacter() {

}
void Ghost::getPacmanCoords(SDL_Rect* pacmanCoords){

}

void Ghost::moveRespawnPos(){
    m_coordinates.x = m_respawnPosition[0] * TILE_SIZE;
    m_coordinates.y = m_respawnPosition[1] * TILE_SIZE;
   /*
    m_startingDestinationReached = false;

    for(auto && wp : wayPointsReached){
        wp = false;
    }
    */
}
