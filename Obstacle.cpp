//
// Created by Tobias on 27.03.2020.
//

#include "Obstacle.h"
Obstacle::Obstacle(const char * fileName, SDL_Renderer* renderer) {
    texture = textureManager.createTexture(fileName, renderer);
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

void Obstacle::setCoordinates(int x, int y, int height, int width) {
    coordinates.x = x;
    coordinates.y = y;
    coordinates.h = height;
    coordinates.w = width;
}

void Obstacle::setTileValue(int value){
    tileValue = value;
}