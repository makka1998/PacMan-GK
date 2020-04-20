
#ifndef PACMAN_GK_MASTER_SCOREDISPLAY_H
#define PACMAN_GK_MASTER_SCOREDISPLAY_H


#include <SDL_pixels.h>
#include <SDL_ttf.h>
#include "iostream"
#include <SDL.h>
#include <SDL2/SDL_ttf.h>

class TextManager {
private:
    std::string m_font_path;
    int m_font_size;
    SDL_Color m_color;
    SDL_Texture *m_textTexture = nullptr;
    SDL_Rect m_textRect;
    std::string m_message_text;

public:
    TextManager(const std::string &font_path, int font_size, const SDL_Color &color);

    void display(int x, int y);

    void loadFont(const std::string &text);

    void displayPoints(int amountOfPoints);

    void displayGameOverText(bool win);
};


#endif //PACMAN_GK_MASTER_SCOREDISPLAY_H
