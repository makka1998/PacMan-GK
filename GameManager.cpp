#include "GameManager.h"
#include "Pacman.h"
#include "Ghost.h"
SDL_Window *window;
SDL_Renderer *GameManager::renderer = nullptr;
Map * level;
Pacman pacman;
Ghost ghost;



int GameManager::playSound(){
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
    }
}

int GameManager::startGame() {
    SDL_Init(SDL_INIT_VIDEO); // Init. SDL2
    windowLoader windowLoader;
    renderManager renderManager;
    playSound();

//    const int FPS = 45;
//    const int frameDelay = 1000 / FPS;
//    Uint32 frameStart;
//    int frameTime;
    SDL_Event event;
    SDL_PollEvent(&event);
    // Lag et vindu med gitte settings
    window = windowLoader.createWindow("Pacman");

    // Lag en renderer til det spesifikke vinduet. Setter Hardware accelerated flag.
    renderer = renderManager.createRenderer(window);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    running = true;
    level = new Map("../Resources/mainLevel.txt");
    auto openingSound = Mix_LoadWAV("../Resources/pacman_beginning.wav");
    if( openingSound == nullptr )
    {
        printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
    }
    Mix_Volume(-1, 5);
    Mix_PlayChannel( -1, openingSound, 0 );
    const Uint8* quitter = SDL_GetKeyboardState(NULL);
    //----------------------------------------------------------------
    while (running) {
        //frameStart = SDL_GetTicks();


        //pacman.calculateDeltaTime();
        pacman.checkMovementInput(level);
        pacman.moveCharacter(level);
        pacman.collisionHandling(level);
        pacman.PickingUpPillHandler(*level);
        ghost.setDistanceToTarget(pacman.getCoords());
        ghost.moveCharacter(level);
        PointsToTextureHandler(pacman.getPointsPickedUp());

        render();
        if(quitter[SDL_SCANCODE_ESCAPE]){
            break;
        }

//        frameTime = SDL_GetTicks() - frameStart;
//        if (frameDelay > frameTime) {
//            SDL_Delay(frameDelay - frameTime);
//        }
    }

    //----------------------------------------------------------------

    SDL_DestroyWindow(window);
    SDL_Quit(); // Be SDL om å rydde opp
    return EXIT_SUCCESS;
}

void GameManager::render() {
    SDL_SetRenderDrawColor(renderer,0,0,0,0);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer,128,128,128,128);

    level->drawMap();
    showGrid();
    pacman.renderCharacter(srect);
    ghost.renderCharacter();
    SDL_RenderPresent(renderer);
}

void GameManager::showGrid(){
    int grid_cell_size = TILE_SIZE;
    int grid_width = 29;
    int grid_height = 36;

    for (int x = 0; x < 1 + grid_width * grid_cell_size;
         x += grid_cell_size) {
        SDL_RenderDrawLine(renderer, x, 0, x, HEIGHT);
    }

    for (int y = 0; y < 1 + grid_height * grid_cell_size;
         y += grid_cell_size) {
        SDL_RenderDrawLine(renderer, 0, y, WIDTH, y);
    }
}

void GameManager::PointsToTextureHandler(int points){
    SDL_Rect source = { 15, 0,TILE_SIZE,TILE_SIZE};
    SDL_Rect destination = { 10, 10, 32, 64 };

}

