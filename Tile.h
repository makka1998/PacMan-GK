
#ifndef PACMAN_GK_MASTER_OBSTACLE_H
#define PACMAN_GK_MASTER_OBSTACLE_H

#include <string>
#include <SDL.h>
#include <SDL_image.h>


class Tile {
private:
    SDL_Texture* m_texture;
    int m_tileValue;
    SDL_Rect m_coordinates, m_src;
    bool m_walkedOver = false;
public:
    Tile(const char * fileName);
    int getTileValue() const {return m_tileValue;}
    SDL_Rect getCoordinates() const {return m_coordinates;}
    SDL_Rect getSrc() const {return m_src;}
    SDL_Texture* getTexture() const {return m_texture;}
    bool getWalkerOver() const {return m_walkedOver;}
    void setCoordinates(int x, int y, int height, int width);
    void setSource(int x, int y, int height, int width);
    void setTileValue(int value);
    void setWalkedOver(bool boolean);
};


#endif //PACMAN_GK_MASTER_OBSTACLE_H
