//
// Created by Tobias on 27.03.2020.
//

#ifndef PACMAN_GK_MASTER_MAP_H
#define PACMAN_GK_MASTER_MAP_H
#define TILE_SIZE 32

#include <string>
#include <vector>
#include "Obstacle.h"
#include "GameManager.h"

class Map {
private:
    std::vector<Obstacle> map;
    int mapX, mapY;

public:
    Map(const char* filePath);
    void loadMap(const char* filePath);
    void drawMap();
    void renderMap(Obstacle tile);
};


#endif //PACMAN_GK_MASTER_MAP_H
