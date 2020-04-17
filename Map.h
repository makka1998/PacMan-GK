//
// Created by Tobias on 27.03.2020.
//

#ifndef PACMAN_GK_MASTER_MAP_H
#define PACMAN_GK_MASTER_MAP_H
#define TILE_SIZE 20

#include <string>
#include <vector>
#include <fstream>
#include "Tile.h"
#include "GameManager.h"

class Map {
private:
public:
    Map() = default;
    Map(const char* filePath);
    void loadMap(const char* filePath);
    void drawMap();
    std::vector<Tile> map;
};


#endif //PACMAN_GK_MASTER_MAP_H
