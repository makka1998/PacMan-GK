
#include "TextManager.h"
#include <iostream>
#include "GameManager.h"
/// https://www.youtube.com/watch?v=FIjj6UVXtXk TextManager with help from this guide.
TextManager::TextManager(const std::string &font_path, int font_size, const SDL_Color &font_color){
    m_font_path = font_path;
    m_font_size = font_size;
    m_color = font_color;

}

void TextManager::display(int x, int y){
    m_textRect.x = x;
    m_textRect.y = y;

    loadFont(m_message_text);
    SDL_QueryTexture(m_textTexture, nullptr, nullptr, &m_textRect.w, &m_textRect.h);

    SDL_RenderCopy(GameManager::renderer, m_textTexture, nullptr, &m_textRect);
    SDL_DestroyTexture(m_textTexture);
}
/**
 * LoadFont will create an texture based on our parameters and with the help of TTF_RenderText_Solid
 *
 * @param font_path is the file-path
 * @param font_size is the size of the font
 * @param message_text is the actual text that you want to render
 * @param color is the color of the text that is being rendered
 */

void TextManager::loadFont(const std::string &text) {
    TTF_Font *font = TTF_OpenFont(m_font_path.c_str(), m_font_size);
    if(font == nullptr){
        std::cerr << "Failed to load font" << std::endl;
    }
    /// since TTF_RenderText_Solid returns an surface, we have to create texture from surface :(
    /// Creating surface and error checking

    SDL_Surface *text_surface  = TTF_RenderText_Solid(font, text.c_str(), m_color); //surface
    if(text_surface == nullptr){ std::cout << "SURFACE ERROR" << std::endl;}
    /// Creating texture from surface text_surface and error checking.


    m_textTexture = SDL_CreateTextureFromSurface(GameManager::renderer, text_surface);
    if(m_textTexture == nullptr){ std::cout << "Texture ERROR" << std::endl;}

    /// Freeing and closing up resources we dont need anymore
    SDL_FreeSurface(text_surface);
    TTF_CloseFont(font);
}

/// Displays the points pacman gets on the top of the screen.
    void TextManager::displayPoints(int amountOfPoints) {
        m_message_text = "points "+ std::to_string(amountOfPoints);
        display(10.2 * TILE_SIZE, 1.5 * TILE_SIZE);
    }

/// This function gets called when you win or lose to render the YOU LOSE/YOU WIN Text.
    void TextManager::displayGameOverText(bool PacmanWon) {
    m_message_text = "GAME OVER";
    display(9.5 * TILE_SIZE, 20 * TILE_SIZE);

    ///YOU lOSE/ YOU WIN based on boolean PacmanWon
    m_message_text = "YOU LOSE";
    if (PacmanWon) {
        m_message_text = "YOU WIN";
        }
    display(10.35 * TILE_SIZE, 14* TILE_SIZE);
}
