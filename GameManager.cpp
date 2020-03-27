#include "GameManager.h"

SDL_Renderer * GameManager::renderer = nullptr;

int GameManager::startGame()
{ // NB: Denne koden tar seg IKKE av feilhåndtering ved init.
    const Uint8* keystate = SDL_GetKeyboardState(NULL);
	bool running = true;
    SDL_Init(SDL_INIT_VIDEO); // Init. SDL2
    windowLoader windowLoader;
    renderManager renderManager;
    TextureManager textureManager;

    const int FPS = 144;
    const int frameDelay = 1000 / FPS;
    Uint32 frameStart;
    int frameTime;
	
    // Lag et vindu med gitte settings
    SDL_Window* window = windowLoader.createWindow("Game Window");
   

    // Lag en renderer til det spesifikke vinduet. Setter Hardware accelerated flag.
    renderer = renderManager.createRenderer(window);

    // Set renderens bakgrunnsfarge til svart
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer); // Nullstiller renderen (til svart)


    // Konverter surface om til et HW Accelerated Texture, laster objektet opp på skjermkortet
    SDL_Texture* drawable = textureManager.createTexture("../Resources/Real_pacman_RIGHT.png", renderer);

    const char * levelFilePath = "../Resources/mainLevel.txt";
    Map level(levelFilePath);

    // Sett opp et "koordinatsystem" for bildet
    SDL_Rect coords;
    coords.h = 32; // Samme bredde og høyde som surface
    coords.w = 32;
    coords.x = 384; // Endre disse for å "flytte" bildet i vinduet/renderer
    coords.y = 304;
/* GAME LOOP START */
    eventHandler chiefInspector;

    while (running) {

        frameStart = SDL_GetTicks();
        SDL_Event event;
        SDL_PollEvent(&event);

        // Legg til objektet i vinduets renderer
        SDL_RenderCopy(renderer, drawable, nullptr, &coords);

        level.drawMap();

        // BLIT/rendre bildet
        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);

        if(keystate[SDL_SCANCODE_ESCAPE] || event.type == SDL_QUIT){
            running = false;
        }

        chiefInspector.checkMovementInput();
        chiefInspector.moveCharacter(coords, drawable, renderer);

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    	
    }

    /* GAME LOOP SLUTT */
	
    SDL_DestroyWindow(window);
    SDL_Quit(); // Be SDL om å rydde opp
	
    return EXIT_SUCCESS;
}
