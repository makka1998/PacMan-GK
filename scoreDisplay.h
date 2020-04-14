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
public:
    scoreDisplay(SDL_Renderer *renderer, const std::string &font_path, int font_size, const std::string &message_text, const SDL_Color &color);

    void display(int x, int y, SDL_Renderer *renderer) const;

    static SDL_Texture *loadFont(SDL_Renderer *renderer, const std::string &font_path, int font_size, const std::string &message_text, const SDL_Color &color);
private:
    SDL_Texture *_text_texture = nullptr;
    mutable SDL_Rect _text_rect;
};


#endif //PACMAN_GK_MASTER_SCOREDISPLAY_H
