//
// Created by Tobias on 27.03.2020.
//

#ifndef PACMAN_GK_MASTER_OBSTACLE_H
#define PACMAN_GK_MASTER_OBSTACLE_H

#include <string>
#include <SDL.h>
#include <SDL_image.h>


class Obstacle {
private:
    SDL_Texture* texture;
    int tileValue;
    SDL_Rect coordinates, src;
public:
    Obstacle(const char * fileName);
    int getTileValue() const;
    SDL_Rect getCoordinates();
    SDL_Rect getSrc();
    SDL_Texture* getTexture() const;
    void setCoordinates(int x, int y, int height, int width);
    void setSource(int x, int y, int height, int width);
    void setTileValue(int value);
    bool WalkedOver = false;
    bool changedNumber;
};


#endif //PACMAN_GK_MASTER_OBSTACLE_H
