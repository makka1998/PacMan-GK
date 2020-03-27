//
// Created by Tobias on 27.03.2020.
//

#include "Map.h"
#include <fstream>
Map::Map(const char * filePath) {
    loadMap(filePath);
}

void Map::loadMap(const char * filePath) {
    Obstacle tmp("../Resources/Pacman_fancy_tileset_16x16.png", GameManager::renderer);
    int currentTileValue, xAxisOfTileset, yAxisOfTileset, startPoint_x, startPoint_y;
    std::ifstream input(filePath); //Our mainLevel.txt file
    if(!input.is_open()){
        std::cerr << "Failed to open file: " << filePath << std::endl;
        return;
    }
    input >> xAxisOfTileset;
    input >> yAxisOfTileset;
    input >> startPoint_x;
    input >> startPoint_y;
    for(int i = 0; i < yAxisOfTileset; i++){
        for(int j = 0; j < xAxisOfTileset; j++){
            input >> currentTileValue;

            // As long as the tileIndex is not 0, it means we need to load a tile from our tileset.
            if(currentTileValue != 0){
                tmp.setSource((currentTileValue-1)*TILE_SIZE, 0, TILE_SIZE, TILE_SIZE);
                tmp.setCoordinates((j*TILE_SIZE) + startPoint_x, (i * TILE_SIZE) + startPoint_y, TILE_SIZE, TILE_SIZE);
                tmp.setTileValue(currentTileValue);
                map.push_back(tmp);
            }
        }
    }
}

void Map::drawMap() {
    for(auto o : map){
        if(o.getCoordinates().x >= TILE_SIZE && o.getCoordinates().y >= TILE_SIZE && o.getCoordinates().x <= WIDTH + TILE_SIZE && o.getCoordinates().y <= HEIGHT + TILE_SIZE){
            renderMap(o);
        }
    }
}

void Map::renderMap(Obstacle tile) {
    //SDL_Rect tileCoords = tile.getCoordinates();
    //SDL_Rect tileSrc = tile.getSrc();
    //Begge "SDL_Rects" står som public i Map.H filen, husk å fiks dette slik at vi kan bruke getters i SDL_Rendercopy!
    SDL_RenderCopy(GameManager::renderer, tile.getTexture(), &tile.src, &tile.coordinates);
}


