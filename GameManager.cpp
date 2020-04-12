#include "GameManager.h"
#include "Pacman.h"
#include "RedGhost.h"
#include "BlueGhost.h"
#include "PinkGhost.h"
#include "OrangeGhost.h"

SDL_Window *window;
SDL_Renderer *GameManager::renderer = nullptr;
double GameManager::deltaTime;
Map * level;
Pacman pacman;
RedGhost Rghost(12, 16, 15, 12, 11, 9, 8, 7 );
BlueGhost Bghost(17, 16, 13, 12, 17, 9, 20, 7);
PinkGhost Pghost(12, 18, 15, 12, 8, 24, 5, 26);
OrangeGhost Oghost(17, 18, 13, 12, 20, 24, 23, 26);

void GameManager::playSound(){
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
        return;
    }
}

int GameManager::startGame() {
    SDL_Init(SDL_INIT_VIDEO); // Init. SDL2
    windowLoader windowLoader;
    renderManager renderManager;
    playSound();

    SDL_Event event;
    SDL_PollEvent(&event);
    // Lag et vindu med gitte settings
    window = windowLoader.createWindow("Pacman");

    // Lag en renderer til det spesifikke vinduet. Setter Hardware accelerated flag.
    renderer = renderManager.createRenderer(window);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    int counter = 0;
    running = true;
    calculateDeltaTime();
    const Uint8 *getKeyboardInput = SDL_GetKeyboardState(NULL);
    //----------------------------------------------------------------
    while(running){

        if(getKeyboardInput[SDL_SCANCODE_U]){
            pacman.setHealth();
        }
        if(getKeyboardInput[SDL_SCANCODE_ESCAPE] || pacman.getHealth() <= 0 || pacman.getPoints() >= 241){
            break;
        }

        /*if(getKeyboardInput[SDL_SCANCODE_P]){
              game_state = 3;
          }
        if(game_state == 3){
            if(getKeyboardInput[SDL_SCANCODE_P])    Dis shitt crashes game :S
            { game_state = 2;}
        }*/
            if(game_state == 1)
            {

                level = new Map("../Resources/mainLevel.txt");
                auto openingSound = Mix_LoadWAV("../Resources/pacman_beginning.wav");
                if (openingSound == nullptr) {
                    printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
                }

                Mix_Volume(-1, 5);
                Mix_PlayChannel(1, openingSound, 0);

                game_state = 2;
            }
            if(game_state == 2)
            {
                calculateDeltaTime();
                pacman.checkMovementInput(level);
                pacman.moveCharacter(level);
                pacman.collisionHandling(level);
                pacman.PickingUpPillHandler(*level);

                Rghost.getMovementDirection(level);
                Rghost.moveCharacter(level);
                Rghost.collisionHandling(level);
                Rghost.isCollidingWithPacman(pacman);

                Pghost.getMovementDirection(level);
                Pghost.moveCharacter(level);
                Pghost.collisionHandling(level);
                Pghost.isCollidingWithPacman(pacman);

                Bghost.getMovementDirection(level);
                Bghost.moveCharacter(level);
                Bghost.collisionHandling(level);
                Bghost.isCollidingWithPacman(pacman);

                Oghost.getMovementDirection(level);
                Oghost.moveCharacter(level);
                Oghost.collisionHandling(level);
                Oghost.isCollidingWithPacman(pacman);
                render();
//                if (pacman.getPoints() == 80) {
//                    game_state = 1;
//                    pacman.setPoints(0);
//                    counter++;
//                }
            }


    }
       /* if(pacman.getPoints() == 240){
            running = false;
        }*/ // If statement for å vinne spillet istedenfor resetting.
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
    if(pacman.getHealth() > 0){
        pacman.renderCharacter(srect);
    } else {
        pacman.ripPacman(deathRect);
    }
    Rghost.renderCharacter();
    Bghost.renderCharacter();
    Pghost.renderCharacter();
    Oghost.renderCharacter();
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

void GameManager::calculateDeltaTime() {
    auto currentFrame = std::chrono::high_resolution_clock::now();
    auto deltaTimeChrono = std::chrono::duration_cast<std::chrono::duration<double>>(currentFrame - m_lastFrame);
    deltaTime = deltaTimeChrono.count();
    m_lastFrame = currentFrame;
}
