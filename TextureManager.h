//
// Created by Tobias on 26.03.2020.
//

#ifndef PACMAN_GK_MASTER_TEXTUREMANAGER_H
#define PACMAN_GK_MASTER_TEXTUREMANAGER_H
#include <SDL.h>
#include <iostream>
#include <SDL_image.h>
#include <string>

class TextureManager {
public:
    SDL_Texture* createTexture(const char * imagePath, SDL_Renderer* renderer);
};

#endif //PACMAN_GK_MASTER_TEXTUREMANAGER_H
