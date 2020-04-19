
#ifndef PACMAN_GK_MASTER_MAP_H
#define PACMAN_GK_MASTER_MAP_H
#define TILE_SIZE 20

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "Tile.h"

class Map {
private:
    std::vector<Tile> map;
public:
    Map(const char* filePath);
    void loadMap(const char* filePath);
    void drawMap();
    std::vector<Tile> * getMap() {return &map;}
};


#endif //PACMAN_GK_MASTER_MAP_H
