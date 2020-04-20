#include "Map.h"
#include "Managers/GameManager.h"

Map::Map(const char *filePath) {
    loadMap(filePath);
}

/**
 * Takes every number inside the TXT file into a tile object and then pushes the tile into a vector
 * @param filePath refers to the TXT files found in the folder Levels
 */
void Map::loadMap(const char *filePath) {
    Tile tmp("../Resources/Images/Pacman_Tileset_20x20.png");
    int currentTileValue, xAxisOfTileset, yAxisOfTileset;
    std::ifstream input(filePath); ///Our mainLevel.txt file
    if (!input.is_open()) {
        std::cerr << "Failed to open file: " << filePath << std::endl;
        return;
    }
    input >> xAxisOfTileset;
    input >> yAxisOfTileset;

    for (int i = 1; i < yAxisOfTileset; i++) {
        for (int j = 0; j < xAxisOfTileset; j++) {
            input >> currentTileValue;
            ///As long as the tileIndex is not 0, it means we need to load a tile from our tile-set. if 0 then just background.
            tmp.setSource((currentTileValue - 1) * TILE_SIZE, 0, TILE_SIZE,
                          TILE_SIZE); ///Which picture we are getting from tile-set.
            tmp.setCoordinates((j * TILE_SIZE), (i * TILE_SIZE), TILE_SIZE, TILE_SIZE); ///Where in the grid.
            tmp.setTileValue(currentTileValue);
            m_map.push_back(tmp);
        }
    }
}

/**
 * Renders the map onto the screen
 */
void Map::drawMap() {
    for (auto &o : m_map) {
        if (o.getWalkerOver()) { o.setSource((0 - 1) * TILE_SIZE, 0, TILE_SIZE, TILE_SIZE); }
        SDL_Rect src = o.getSrc();
        SDL_Rect coordinates = o.getCoordinates();
        SDL_RenderCopy(GameManager::renderer, o.getTexture(), &src, &coordinates);
    }
}
