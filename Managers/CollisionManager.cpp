#include "CollisionManager.h"
#include "../Characters/GameCharacter.h"


/**
 * Checking if a gameCharacter collides with an obstacle, if it does it gets pushed back into the playing field. Where to set it after a collision depends on what kind of obstacle it collides with.
 * @param map Container with all the tiles the level is made up of.
 */
void CollisionManager::collisionHandling(Map &map, SDL_Rect &m_coordinates, direction &m_direction) {
    ///Checking every tile to see if you collided with it.
    for (Tile o : *map.getMap()) {
        SDL_Rect tmp = o.getCoordinates();
        if (SDL_HasIntersection(&m_coordinates, &tmp)) {
            if (o.getTileValue() == 3) { ///Horizontal obstacles
                if (m_direction == direction::DOWN || m_direction == direction::RIGHT ||
                    m_direction == direction::LEFT) {
                    m_coordinates.y = o.getCoordinates().y - TILE_SIZE;
                } else if (m_direction == direction::UP) {
                    m_coordinates.y = o.getCoordinates().y + TILE_SIZE;
                }
            }

            if (o.getTileValue() == 4 || o.getTileValue() == 5) {///Vertical obstacles
                if (m_direction == direction::LEFT) {
                    m_coordinates.x = o.getCoordinates().x + TILE_SIZE;
                } else if (m_direction == direction::RIGHT) {
                    m_coordinates.x = o.getCoordinates().x - TILE_SIZE;
                }
            }

            if (o.getTileValue() == 1 || o.getTileValue() == 11) {///Top-left corner
                if (m_direction == direction::DOWN || m_direction == direction::RIGHT) {
                    m_coordinates.x = o.getCoordinates().x - TILE_SIZE;
                    m_coordinates.y = o.getCoordinates().y - TILE_SIZE;
                }
            }

            if (o.getTileValue() == 2 || o.getTileValue() == 12) {///Top-right corner
                if (m_direction == direction::DOWN || m_direction == direction::LEFT) {
                    m_coordinates.x = o.getCoordinates().x + TILE_SIZE;
                    m_coordinates.y = o.getCoordinates().y - TILE_SIZE;
                }
            }

            if (o.getTileValue() == 7 || o.getTileValue() == 13) {///Bottom-left corner
                if (m_direction == direction::RIGHT || m_direction == direction::UP) {
                    m_coordinates.x = o.getCoordinates().x - TILE_SIZE;
                    m_coordinates.y = o.getCoordinates().y + TILE_SIZE;
                }
            }

            if (o.getTileValue() == 8 || o.getTileValue() == 14) {///Bottom-right corner
                if (m_direction == direction::LEFT || m_direction == direction::UP) {
                    m_coordinates.x = o.getCoordinates().x + TILE_SIZE;
                    m_coordinates.y = o.getCoordinates().y + TILE_SIZE;
                }
            }
        }
    }
}