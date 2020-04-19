
#include "Tile.h"
#include "Managers/GameManager.h"
/// This entire class is used to get information about the Tiles on the map.
Tile::Tile(const char *fileName) : m_texture(IMG_LoadTexture(GameManager::renderer, fileName)) {
    if (m_texture == nullptr) {
        std::cout << "load m_texture failure" << std::endl;
    }
}

void Tile::setCoordinates(int x, int y, int height, int width) {
    m_coordinates.x = x;
    m_coordinates.y = y;
    m_coordinates.h = height;
    m_coordinates.w = width;
}

void Tile::setSource(int x, int y, int height, int width) {
    m_src.x = x;
    m_src.y = y;
    m_src.w = width;
    m_src.h = height;
}

void Tile::setTileValue(int value) {
    m_tileValue = value;
}

void Tile::setWalkedOver(bool boolean){
    m_walkedOver = boolean;
}
