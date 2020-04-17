//
// Created by Tobias on 27.03.2020.
//

#include "Tile.h"
#include "GameManager.h"

Tile::Tile(const char * fileName) : texture(IMG_LoadTexture(GameManager::renderer, fileName)) {
    if(texture == nullptr){
        std::cout <<"load texture failure" << std::endl;
    }
}

int Tile::getTileValue() const {
    return tileValue;
}

SDL_Texture* Tile::getTexture() const {
    return texture;
}

SDL_Rect Tile::getCoordinates() {
    return coordinates;
}

SDL_Rect Tile::getSrc(){
    return src;
}

void Tile::setCoordinates(int x, int y, int height, int width) {
    coordinates.x = x;
    coordinates.y = y;
    coordinates.h = height;
    coordinates.w = width;
}

void Tile::setSource(int x, int y, int height, int width) {
    src.x=x;
    src.y=y;
    src.w=width;
    src.h=height;
}

void Tile::setTileValue(int value){
    tileValue = value;
}
