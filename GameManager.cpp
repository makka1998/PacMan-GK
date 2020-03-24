#include "GameManager.h"
#include "windowLoader.h"
#include "renderManager.h"
#include "TextureManager.h"
#include <iostream>
#include <SDL.h>

int GameManager::startGame()
{ // NB: Denne koden tar seg IKKE av feilhåndtering ved init.
    const Uint8* keystate;
	bool running = true;
    SDL_Init(SDL_INIT_VIDEO); // Init. SDL2
    windowLoader windowLoader;
    renderManager renderManager;
    textureManager textureManager;

    const int FPS = 144;
    const int frameDelay = 1000 / FPS;
    Uint32 frameStart;
    int frameTime;
	
    // Lag et vindu med gitte settings
    SDL_Window* window = windowLoader.createWindow("Hei hei idiot", 542, 571);
   

    // Lag en renderer til det spesifikke vinduet. Setter Hardware accelerated flag.
    SDL_Renderer* renderer = renderManager.createRenderer(window);

    // Set renderens bakgrunnsfarge til svart
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer); // Nullstiller renderen (til svart)


    // Konverter surface om til et HW Accelerated Texture, laster objektet opp på skjermkortet
    SDL_Texture* drawable = textureManager.createTexture("../Resources/pacman.png", renderer);
  
    // Sett opp et "koordinatsystem" for bildet
    SDL_Rect coords;
    coords.h = 250; // Samme bredde og høyde som surface
    coords.w = 250;
    coords.x = 0; // Endre disse for å "flytte" bildet i vinduet/renderer
    coords.y = 0;


/* GAME LOOP START */

    while (running) {

        frameStart = SDL_GetTicks();
        SDL_Event event;
        SDL_PollEvent(&event);
    	
        // Legg til objektet i vinduets renderer
        SDL_RenderCopy(renderer, drawable, nullptr, &coords);

        // BLIT/rendre bildet
        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);

        switch (event.type)
        {
        case SDL_QUIT:
            running = false;
            break;
        default:
            break;
        }

        keystate = SDL_GetKeyboardState(NULL);
    	if(keystate[SDL_SCANCODE_D] || keystate[SDL_SCANCODE_RIGHT])
    	{
            coords.x += 1;
    	} else if(keystate[SDL_SCANCODE_A] || keystate[SDL_SCANCODE_LEFT])
    	{
            coords.x += -1;
    	} else if(keystate[SDL_SCANCODE_W] || keystate[SDL_SCANCODE_UP])
    	{
            coords.y += -1;
    	} else if(keystate[SDL_SCANCODE_S] || keystate[SDL_SCANCODE_DOWN ])
    	{
            coords.y += 1;
    	}

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
