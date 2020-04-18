
#include "Tile.h"
#include "Managers/GameManager.h"
/// This entire class is used to get information about the Tiles on the map.
Tile::Tile(const char *fileName) : m_texture(IMG_LoadTexture(GameManager::renderer, fileName)) {
    if (m_texture == nullptr) {
        std::cout << "load m_texture failure" << std::endl;
    }
}

int Tile::getTileValue() const {
    return m_tileValue;
}

SDL_Texture *Tile::getTexture() const {
    return m_texture;
}

SDL_Rect Tile::getCoordinates() {
    return m_coordinates;
}

SDL_Rect Tile::getSrc() {
    return m_src;
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
