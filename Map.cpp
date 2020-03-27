//
// Created by Tobias on 27.03.2020.
//

#include "Map.h"
#include <fstream>
Map::Map(const char * filePath) {
    loadMap(filePath);
}

void Map::loadMap(const char * filePath) {
    Obstacle tmp("../Resources/Pacman_16x16_Tileset_Blue.png", GameManager::renderer);
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


