//
// Created by Tobias on 27.03.2020.
//

#include "Map.h"
#include <fstream>
Map::Map(const char * filePath) {
    loadMap(filePath);
}

void Map::loadMap(const char * filePath) {
    Obstacle tmp("../Resources/Pacman_fancy_tileset.png", GameManager::renderer);
    int currentTileValue, xAxisOfTileset, yAxisOfTileset;
    std::ifstream input(filePath);
    if(!input.is_open()){
        std::cerr << "Failed to open file: " << filePath << std::endl;
        SDL_Quit();
    }

    input >> xAxisOfTileset;
    input >> yAxisOfTileset;

    for(int i = 0; i < yAxisOfTileset; i++){
        for(int j = 0; j < xAxisOfTileset; j++){
            input >> currentTileValue;

            // As long as the tileIndex is not 0, it means we need to load a tile from out tileset.
            if(currentTileValue != 0){
                tmp.setCoordinates((j*TILE_SIZE), (i * TILE_SIZE), TILE_SIZE, TILE_SIZE);
                tmp.setTileValue(currentTileValue);
                map.push_back(tmp);
            }
        }
    }
}

void Map::drawMap() {
    for(Obstacle o : map){
        if(o.coordinates.x >= TILE_SIZE && o.coordinates.y >= TILE_SIZE && o.coordinates.x <= WIDTH + TILE_SIZE && o.coordinates.y <= HEIGHT + TILE_SIZE){
            renderMap(o);
        }
    }
}

void Map::renderMap(Obstacle tile) {
    SDL_Rect tileCoords = tile.getCoordinates();
    SDL_RenderCopy(GameManager::renderer, tile.getTexture(), nullptr, &tileCoords);
}


