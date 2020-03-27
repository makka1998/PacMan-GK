//
// Created by Tobias on 27.03.2020.
//

#ifndef PACMAN_GK_MASTER_OBSTACLE_H
#define PACMAN_GK_MASTER_OBSTACLE_H

#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "TextureManager.h"

class Obstacle {
private:
    TextureManager textureManager;
    SDL_Texture* texture;
    int tileValue;
public:
    SDL_Rect coordinates;
    Obstacle(const char * fileName, SDL_Renderer* renderer);
    int getTileValue() const;
    SDL_Rect getCoordinates() const;
    SDL_Texture* getTexture() const;
    void setCoordinates(int x, int y, int height, int width);
    void setTileValue(int value);
};


#endif //PACMAN_GK_MASTER_OBSTACLE_H
