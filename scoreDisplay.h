//
// Created by Martin on 12.04.2020.
//

#ifndef PACMAN_GK_MASTER_SCOREDISPLAY_H
#define PACMAN_GK_MASTER_SCOREDISPLAY_H


#include <SDL_pixels.h>
#include <SDL_ttf.h>
#include "iostream"
#include <SDL.h>
#include <SDL2/SDL_ttf.h>

class scoreDisplay {
private:
    SDL_Texture * m_textTexture = nullptr;

    mutable SDL_Rect m_textRect;

public:
    scoreDisplay(SDL_Renderer *renderer, const std::string &font_path, int font_size, const std::string &message_text, const SDL_Color &color);
    void display(int x, int y, SDL_Renderer *renderer) const;
    static SDL_Texture *loadFont(SDL_Renderer *renderer, const std::string &font_path, int font_size, const std::string &message_text, const SDL_Color &color);
};


#endif //PACMAN_GK_MASTER_SCOREDISPLAY_H
