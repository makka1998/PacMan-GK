//
// Created by Tobias on 27.03.2020.
//

#include "Map.h"
#include <fstream>
Map::Map(const char * filePath) {
    loadMap(filePath);
}

void Map::loadMap(const char * filePath) {
    Obstacle tmp("../Resources/Pacman_16x16_Tileset_Blue.png");
    int currentTileValue, xAxisOfTileset, yAxisOfTileset, startPoint_x, startPoint_y;
    std::ifstream input(filePath); //Our mainLevel.txt file
    if(!input.is_open()){
        std::cerr << "Failed to open file: " << filePath << std::endl;
        return;
    }
    input >> xAxisOfTileset;
    input >> yAxisOfTileset;
    startPoint_x = startPoint_y = 0;
    for(int i = 1; i < yAxisOfTileset; i++){
        for(int j = 0; j < xAxisOfTileset; j++){
            input >> currentTileValue;

                // As long as the tileIndex is not 0, it means we need to load a tile from our tileset.
                tmp.setSource((currentTileValue-1)*TILE_SIZE, 0, 16, 16); //wich picture we are getting from tileset.
                if(j == 0 && i == 1){
                    tmp.setCoordinates(0, 0, TILE_SIZE, TILE_SIZE); //Hvor i griden
                }
                tmp.setCoordinates((j*TILE_SIZE) + startPoint_x, (i * TILE_SIZE) + startPoint_y, TILE_SIZE, TILE_SIZE); //Hvor i griden
                tmp.setTileValue(currentTileValue);
                map.push_back(tmp);

        }
    }
}

void Map::drawMap() {
    for(auto o : map){
        if(o.getCoordinates().x >= TILE_SIZE && o.getCoordinates().y >= TILE_SIZE && o.getCoordinates().x <= WIDTH + TILE_SIZE && o.getCoordinates().y <= HEIGHT + TILE_SIZE){
            SDL_Rect src = o.getSrc();
            SDL_Rect coordinates = o.getCoordinates();
            SDL_RenderCopy(GameManager::renderer, o.getTexture(), &src, &coordinates);
        }
    }
}