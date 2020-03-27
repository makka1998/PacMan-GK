#ifndef PAC_MAN_GK_WINDOWLOADER_H
#define PAC_MAN_GK_WINDOWLOADER_H

#include <SDL.h>
#define WIDTH 900
#define HEIGHT 1000

class windowLoader {
public:
	SDL_Window* createWindow(const char* title);
};

#endif //PACMAN_GK_MASTER_WINDOWLOADER_H