#include "GameManager.h"
#include "Pacman.h"

SDL_Window *window;
SDL_Renderer *GameManager::renderer = nullptr;
Map * level;
Pacman pacman;
int GameManager::startGame() {

    SDL_Init(SDL_INIT_VIDEO); // Init. SDL2
    windowLoader windowLoader;
    renderManager renderManager;

    const int FPS = 60;
    const int frameDelay = 1000 / FPS;
    Uint32 frameStart;
    int frameTime;
    SDL_Event event;
    SDL_PollEvent(&event);
    // Lag et vindu med gitte settings
    window = windowLoader.createWindow("Pacman");

    // Lag en renderer til det spesifikke vinduet. Setter Hardware accelerated flag.
    renderer = renderManager.createRenderer(window);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    running = true;
    level = new Map("../Resources/mainLevel.txt");
    const Uint8* quitter = SDL_GetKeyboardState(NULL);
    while (running) {
        frameStart = SDL_GetTicks();

        if(pacman.pathAvailable(level)) {
            pacman.checkMovementInput();
        }
        pacman.moveCharacter(level);
        pacman.collisionHandling(level);
        render();
        if(quitter[SDL_SCANCODE_ESCAPE]){
            break;
        }

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit(); // Be SDL om å rydde opp
    return EXIT_SUCCESS;
}

void GameManager::render() {
    SDL_RenderClear(renderer);
    level->drawMap();
    pacman.renderCharacter();
    SDL_RenderPresent(renderer);
}
