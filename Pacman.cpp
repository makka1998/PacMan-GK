//
// Created by Tobias on 28.03.2020.
//

#include "Pacman.h"

Pacman::Pacman() {
    m_coordinates.x = 14 * TILE_SIZE;
    m_coordinates.y = 26 * TILE_SIZE;

    m_coordinates.h = TILE_SIZE;
    m_coordinates.w = TILE_SIZE;
}
void Pacman::PickingUpPillHandler(Map &map) {
    int player_X = round((m_coordinates.x + (m_coordinates.w) / 2) / TILE_SIZE);
    int player_Y = round((m_coordinates.y + (m_coordinates.h) / 2) / TILE_SIZE);

    for (auto& tile : map.map) {
        int tile_X = tile.getCoordinates().x/TILE_SIZE;
        int tile_Y = tile.getCoordinates().y/TILE_SIZE;
        if (player_X == tile_X && player_Y == tile_Y) {
            if (tile.getTileValue() == 10) {

                //Plukk opp pillene
                point += 1;
                tile.setTileValue(0);
                tile.WalkedOver=true;
                playPillSound();

            } else if(tile.getTileValue() == 9){
                tile.setTileValue(0);
                tile.WalkedOver=true;
                m_powerUpDuration = 0;
            }

        }
    }
    m_powerUpDuration += GameManager::deltaTime;
}

void Pacman::renderCharacter(SDL_Rect srect []) {
    m_texture = IMG_LoadTexture(GameManager::renderer,"../Resources/Old_Tilesets/PacManSpriteSheet_20x20.png");
    timer += GameManager::deltaTime;
    if (timer <=0.1) {
        m_animationNumber = 0;
        srect[0].x = TILE_SIZE;
        srect[0].y = TILE_SIZE;
        srect[0].h = TILE_SIZE;
        srect[0].w = TILE_SIZE;
    } else if (timer <=0.2) {
        m_animationNumber = 1;
        srect[1].x =  0;
        srect[1].y = TILE_SIZE;
        srect[1].h = TILE_SIZE;
        srect[1].w = TILE_SIZE;
    } else if (timer <=0.3) {
        m_animationNumber = 2;
        srect[2].x = TILE_SIZE*2;
        srect[2].y =  0;
        srect[2].h = TILE_SIZE;
        srect[2].w = TILE_SIZE;
    } else if(timer <=0.4){
        timer = 0;
    }
    SDL_RenderCopyEx(GameManager::renderer, m_texture, &srect[m_animationNumber], &m_coordinates, angle, &center, SDL_FLIP_NONE);
    SDL_DestroyTexture(m_texture);
}

void Pacman::ripPacman(SDL_Rect srect []){
    if(m_animationNumber > 11){
        m_animationNumber = 1;
    }
    int deathPosition  = 200;
    m_texture = IMG_LoadTexture(GameManager::renderer, "../Resources/Old_Tilesets/PacManSpriteSheet_20x20.png");
        if (m_animationNumber == 1) {
            srect[0].x = TILE_SIZE*0;
            srect[0].y = deathPosition;
            srect[0].h = TILE_SIZE;
            srect[0].w = TILE_SIZE;
        } else if (m_animationNumber == 2) {
            srect[1].x = TILE_SIZE;
            srect[1].y = deathPosition;
            srect[1].h = TILE_SIZE;
            srect[1].w = TILE_SIZE;
        } else if (m_animationNumber == 3) {
            srect[2].x = TILE_SIZE*2;
            srect[2].y = deathPosition;
            srect[2].h = TILE_SIZE;
            srect[2].w = TILE_SIZE;
        } else if (m_animationNumber == 4) {
            srect[3].x = TILE_SIZE*3;
            srect[3].y = deathPosition;
            srect[3].h = TILE_SIZE;
            srect[3].w = TILE_SIZE;
        } else if (m_animationNumber == 5) {
            srect[4].x = TILE_SIZE*4;
            srect[4].y = deathPosition;
            srect[4].h = TILE_SIZE;
            srect[4].w = TILE_SIZE;
        } else if (m_animationNumber == 6) {
            srect[5].x = TILE_SIZE*5;
            srect[5].y = deathPosition;
            srect[5].h = TILE_SIZE;
            srect[5].w = TILE_SIZE;
        } else if (m_animationNumber == 7) {
            srect[6].x = TILE_SIZE*6;
            srect[6].y = deathPosition;
            srect[6].h = TILE_SIZE;
            srect[6].w = TILE_SIZE;
        } else if (m_animationNumber == 8) {
            srect[7].x = TILE_SIZE*7;
            srect[7].y = deathPosition;
            srect[7].h = TILE_SIZE;
            srect[7].w = TILE_SIZE;
        } else if (m_animationNumber == 9) {
            srect[8].x = TILE_SIZE*8;
            srect[8].y = deathPosition;
            srect[8].h = TILE_SIZE;
            srect[8].w = TILE_SIZE;
        } else if (m_animationNumber == 10) {
            srect[9].x = TILE_SIZE*9;
            srect[9].y = deathPosition;
            srect[9].h = TILE_SIZE;
            srect[9].w = TILE_SIZE;
        } else if (m_animationNumber == 11) {
            srect[10].x = TILE_SIZE*10;
            srect[10].y = deathPosition;
            srect[10].h = TILE_SIZE;
            srect[10].w = TILE_SIZE;
        }
        SDL_RenderCopy(GameManager::renderer, m_texture, &srect[m_animationNumber - 1], &m_coordinates);
        SDL_DestroyTexture(m_texture);
}

 SDL_Rect * Pacman::getCoords(){
    return &m_coordinates;
}

direction Pacman::getDirection() {
    return m_direction;
}

void Pacman::playPillSound(){
    eatPillSound = Mix_LoadWAV("../Resources/EatPillSound3.wav");
    if(eatPillSound == nullptr ){
        printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
    }

    if(Mix_Playing(-1) == 0){
        //Play the music
        Mix_PlayChannel(1, eatPillSound, 0 );
    }
}
void Pacman::startPos(){
    m_coordinates.x = 14 * TILE_SIZE;
    m_coordinates.y = 26 * TILE_SIZE;
    m_direction = direction::NONE;
}