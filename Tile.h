
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
public:
    Tile(const char * fileName);
    int getTileValue() const;
    SDL_Rect getCoordinates();
    SDL_Rect getSrc();
    SDL_Texture* getTexture() const;
    void setCoordinates(int x, int y, int height, int width);
    void setSource(int x, int y, int height, int width);
    void setTileValue(int value);
    bool WalkedOver = false;
};


#endif //PACMAN_GK_MASTER_OBSTACLE_H
