#ifndef PAC_MAN_GK_RENDERMANAGER_H
#define PAC_MAN_GK_RENDERMANAGER_H

#include <SDL2/SDL.h>
#include <iostream>


class RenderManager {
public:
    SDL_Renderer *createRenderer(SDL_Window *window);
};

#endif //PACMAN_GK_MASTER_RENDERMANAGER_h

