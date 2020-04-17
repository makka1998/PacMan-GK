#ifndef PAC_MAN_GK_WINDOWLOADER_H
#define PAC_MAN_GK_WINDOWLOADER_H

#include <SDL.h>
#define WIDTH 562           //Change to 465 for 16x16 px
#define HEIGHT 740         //Change to 592 for 16x16 px

class WindowLoader {
public:
    SDL_Window* createWindow(const char* title);
};

#endif //PACMAN_GK_MASTER_WINDOWLOADER_H