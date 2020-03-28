//
// Created by Tobias on 27.03.2020.
//

#include "Obstacle.h"
#include "GameManager.h"

Obstacle::Obstacle(const char * fileName) {
    texture = IMG_LoadTexture(GameManager::renderer, fileName);
    if(texture == nullptr){
        std::cout <<"load texture failure" << std::endl;
    }
}

int Obstacle::getTileValue() const {
    return tileValue;
}

SDL_Texture* Obstacle::getTexture() const {
    return texture;
}

SDL_Rect Obstacle::getCoordinates() const {
    return coordinates;
}

SDL_Rect Obstacle::getSrc() const {
    return src;
}

void Obstacle::setCoordinates(int x, int y, int height, int width) {
    coordinates.x = x;
    coordinates.y = y;
    coordinates.h = height;
    coordinates.w = width;
}

void Obstacle::setSource(int x, int y, int height, int width) {
    src.x=x;
    src.y=y;
    src.w=width;
    src.h=height;
}

void Obstacle::setTileValue(int value){
    tileValue = value;
}
