
#include "TextManager.h"
#include <iostream>
#include "GameManager.h"

void TextManager::display(int x, int y, SDL_Renderer *renderer) const{
    m_textRect.x = x;
    m_textRect.y = y;
    SDL_RenderCopy(renderer, m_textTexture, nullptr, &m_textRect);
    SDL_DestroyTexture(m_textTexture);
}

SDL_Texture *TextManager::loadFont(SDL_Renderer *renderer, const std::string &font_path, int font_size, const std::string &message_text, const SDL_Color &color){
    TTF_Font *font = TTF_OpenFont(font_path.c_str(), font_size);
    if(!font){
        std::cerr << "Failed to load font" << std::endl;
    }
    auto text_surface = TTF_RenderText_Solid(font, message_text.c_str(), color);
    if(!text_surface) {
        std::cerr << "Failed to create text surface" << TTF_GetError << std::endl;
    }
    auto text_texture = SDL_CreateTextureFromSurface(GameManager::renderer, text_surface);
    if(!text_texture) {
        std::cerr << "Failed to create text surface" << std::endl;
    }
    SDL_FreeSurface(text_surface);
    TTF_CloseFont(font);
    return text_texture;
}
TextManager::TextManager(
        SDL_Renderer *renderer,
        const std::string &font_path,
        int font_size,
        const std::string &message_text,
        const SDL_Color &color)
{
    m_textTexture = loadFont(renderer, font_path, font_size, message_text, color);
    SDL_QueryTexture(m_textTexture, nullptr, nullptr, &m_textRect.w, &m_textRect.h);
}
