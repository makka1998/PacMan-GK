//
// Created by Tobias on 28.03.2020.
//

#include "Pacman.h"

Pacman::Pacman() {
    m_coordinates.x = 14.5 * TILE_SIZE;
    m_coordinates.y = 26 * TILE_SIZE;

    m_coordinates.h = TILE_SIZE - 1;
    m_coordinates.w = TILE_SIZE - 1;
}
int counter = 0;
void Pacman::PickingUpPillHandler(Map &map) {

    //Pacman's position in ratio of the grid/tiles.
    int player_X = round((m_coordinates.x + (m_coordinates.w) / 2) / TILE_SIZE);
    int player_Y = round((m_coordinates.y + (m_coordinates.h) / 2) / TILE_SIZE);
    for (auto& tile : map.map) {
        int tile_X = tile.getCoordinates().x/TILE_SIZE;
        int tile_Y = tile.getCoordinates().y/TILE_SIZE;
        if (player_X == tile_X && player_Y == tile_Y) {
            if (tile.getTileValue() == 10) {
                //Plukk opp pillene
                point++;
                std::cout << "Poeng: " << point << std::endl;
                tile.setTileValue(0);
                tile.WalkedOver=true;
            }

        }
    }
}

void Pacman::renderCharacter(SDL_Rect srect []) {
    //m_texture = IMG_LoadTexture(GameManager::renderer, "../Resources/PacManSpriteSheet_16x16.png");
    m_texture = IMG_LoadTexture(GameManager::renderer, "../Resources/Old_Tilesets/PacManSpriteSheet_20x20.png");
    if (animationNumber == 1) {
        srect[0].x = TILE_SIZE;
        srect[0].y = TILE_SIZE;
        srect[0].h = TILE_SIZE;
        srect[0].w = TILE_SIZE;
        //std::cout << "1: " << std::endl;
    } else if (animationNumber == 2) {
        srect[1].x = TILE_SIZE;
        srect[1].y = TILE_SIZE;
        srect[1].h = TILE_SIZE;
        srect[1].w = TILE_SIZE;
        std::cout << "2: " << std::endl;
    } else if (animationNumber == 3) {
        srect[2].x = TILE_SIZE;
        srect[2].y = TILE_SIZE;
        srect[2].h = TILE_SIZE;
        srect[2].w = TILE_SIZE;
        std::cout << "3: " << std::endl;
    } else if (animationNumber == 4) {
        srect[3].x =  0;
        srect[3].y = TILE_SIZE;
        srect[3].h = TILE_SIZE;
        srect[3].w = TILE_SIZE;
        std::cout << "4: " << std::endl;
    } else if (animationNumber == 5) {
        srect[4].x =  0;
        srect[4].y = TILE_SIZE;
        srect[4].h = TILE_SIZE;
        srect[4].w = TILE_SIZE;
        std::cout << "1: " << std::endl;
    } else if (animationNumber == 6) {
        srect[5].x =  0;
        srect[5].y = TILE_SIZE;
        srect[5].h = TILE_SIZE;
        srect[5].w = TILE_SIZE;
        std::cout << "2: " << std::endl;
    } else if (animationNumber == 7) {
        srect[6].x = TILE_SIZE*2;
        srect[6].y =  0;
        srect[6].h = TILE_SIZE;
        srect[6].w = TILE_SIZE;
        std::cout << "40: " << std::endl;
    } else if (animationNumber == 8) {
        srect[7].x = TILE_SIZE*2;
        srect[7].y =  0;
        srect[7].h = TILE_SIZE;
        srect[7].w = TILE_SIZE;
        std::cout << "40: " << std::endl;
    } else if (animationNumber == 9) {
        srect[8].x = TILE_SIZE*2;
        srect[8].y =  0;
        srect[8].h = TILE_SIZE;
        srect[8].w = TILE_SIZE;
        //std::cout << "1: " << std::endl;
    } else if (animationNumber == 10) {
        srect[9].x =  0;
        srect[9].y = TILE_SIZE;
        srect[9].h = TILE_SIZE;
        srect[9].w = TILE_SIZE;
        //std::cout << "2: " << std::endl;
    } else if (animationNumber == 11) {
        srect[10].x =  0;
        srect[10].y = TILE_SIZE;
        srect[10].h = TILE_SIZE;
        srect[10].w = TILE_SIZE;
        //std::cout << "3: " << std::endl;
    } else if (animationNumber == 12) {
        srect[11].x =  0;
        srect[11].y = TILE_SIZE;
        srect[11].h = TILE_SIZE;
        srect[11].w = TILE_SIZE;
        // std::cout << "4: " << std::endl;
    }
    SDL_RenderCopyEx(GameManager::renderer, m_texture, &srect[animationNumber - 1], &m_coordinates, angle, &center, SDL_FLIP_NONE);
}
