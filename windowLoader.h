#ifndef PAC_MAN_GK_WINDOWLOADER_H
#define PAC_MAN_GK_WINDOWLOADER_H

#include <SDL.h>
#define WIDTH 464
#define HEIGHT 592

class windowLoader {
public:
	SDL_Window* createWindow(const char* title);
};

#endif //PACMAN_GK_MASTER_WINDOWLOADER_H