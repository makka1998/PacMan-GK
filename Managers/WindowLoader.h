#ifndef PAC_MAN_GK_WINDOWLOADER_H
#define PAC_MAN_GK_WINDOWLOADER_H

#include <SDL.h>
///Window size
#define WIDTH 562
#define HEIGHT 740

class WindowLoader {
public:
    SDL_Window *createWindow(const char *title);
};

#endif //PACMAN_GK_MASTER_WINDOWLOADER_H