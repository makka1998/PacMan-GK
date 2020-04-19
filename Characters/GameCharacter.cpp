
#include "GameCharacter.h"
#include "../Managers/GameManager.h"
/**
 * Sets the "spawn" location for the gameCharacter.
 * @param xs x-coordinate it starts on.
 * @param ys y-coordinate it starts on.
 */
GameCharacter::GameCharacter(int x, int y, int speed){
    m_coordinates = {x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE};
    m_speed = speed;
}

void GameCharacter::characterHandler(Map &map){
    ///Movement Handling
    m_movementManager.moveCharacter(m_speed,m_coordinates,m_direction);
    m_movementManager.pathAvailable(map,m_coordinates);
    ///Collision Handling
    m_collisionManager.collisionHandling(map,m_coordinates,m_direction);
}

