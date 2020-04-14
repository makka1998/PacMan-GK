#include "GameManager.h"
#include "Pacman.h"
#include "RedGhost.h"
#include "BlueGhost.h"
#include "PinkGhost.h"
#include "OrangeGhost.h"
#include "SDL2/SDL_ttf.h"
#include "scoreDisplay.h"
#include <string>

SDL_Window *window;
SDL_Renderer *GameManager::renderer = nullptr;
double GameManager::deltaTime;
Map * level;
Pacman pacman;

GameManager::GameManager(){

    SDL_Rect* pacmanCoords = pacman.getCoords();
    m_gameCharacters.push_back(std::make_shared<RedGhost>(12, 16, 10, 11, 15, 12, 11, 9, 8, 7));
    m_gameCharacters.push_back(std::make_shared<BlueGhost>(17, 16, 19, 11, 13, 12, 17, 9, 20, 7));
    m_gameCharacters.push_back(std::make_shared<PinkGhost>(12, 18, 10, 14, 15, 12, 8, 24, 5, 26));
    m_gameCharacters.push_back(std::make_shared<OrangeGhost>(17, 18, 19, 14, 13, 12, 20, 24, 23, 26));
}

void GameManager::playSound(){
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
        return;
    }
}

void GameManager::renderMainMenu(){
    timer += GameManager::deltaTime;
    SDL_Texture* background = IMG_LoadTexture(GameManager::renderer, "../Resources/Old_Tilesets/mainMenu_1.png");
    if (timer >=0.5) {
        SDL_DestroyTexture(background);
        background = IMG_LoadTexture(GameManager::renderer, "../Resources/Old_Tilesets/mainMenu_2.png");
        if(timer >=1 ){
            timer= 0;
        }
    }
        SDL_RenderCopy(GameManager::renderer, background, nullptr, nullptr);
        SDL_DestroyTexture(background);
}
int GameManager::startGame() {
    srand(time(NULL));
    SDL_Init(SDL_INIT_VIDEO); // Init. SDL2
    windowLoader windowLoader;
    renderManager renderManager;
    TTF_Init();

    window = windowLoader.createWindow("Pacman");
    renderer = renderManager.createRenderer(window);
    playSound();

    SDL_Event event;
    SDL_PollEvent(&event);

    running = true;
    bool pause = true;
    calculateDeltaTime();
    const Uint8 *getKeyboardInput = SDL_GetKeyboardState(NULL);
    //----------------------------------------------------------------
    while(running){
        while(pause){
            calculateDeltaTime();
            ghostMovementWrapper(pause);
            pacmanWrapper(pause);
            render(pause);

            if(getKeyboardInput[SDL_SCANCODE_RETURN]){
                pause=false;
            }
        }
        if(getKeyboardInput[SDL_SCANCODE_ESCAPE] || pacman.getHealth() <= 0 || pacman.getPoints() >= 241){
           break;
        }
            if(game_state == 1){
                level = new Map("../Resources/mainLevel.txt");
                //Opening sound
                auto openingSound = Mix_LoadWAV("../Resources/pacman_beginning.wav");
                if (openingSound == nullptr) {printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());}
                Mix_Volume(-1, 5);
                Mix_PlayChannel(-1, openingSound, 0);
                    game_state = 2;
            }
            if(game_state == 2){
                calculateDeltaTime();
                pacmanWrapper(pause);
                ghostMovementWrapper(pause);
                render(pause);

                if(getKeyboardInput[SDL_SCANCODE_P]){
                    pause = true;
                }
        }
    }
    quit();
    return EXIT_SUCCESS;
}
void GameManager::quit(){
    SDL_DestroyWindow(window);
    SDL_Quit(); // Be SDL om å rydde opp
};
void GameManager::render(bool pause) {
    SDL_SetRenderDrawColor(renderer,0,0,0,0);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer,255,255,255,0);
    if(pause){
        renderMainMenu();
    }else {
        std::string poeng = std::to_string(pacman.getPoints());
        scoreDisplay score(GameManager::renderer, "../Resources/Old_Tilesets/Arial.ttf", 1*TILE_SIZE, "Poeng: "+poeng , {255,255,255,255});
        score.display(13*TILE_SIZE,1.5*TILE_SIZE, renderer);

        level->drawMap();
        //showGrid();
        if(pacman.getHealth() > 0){
            pacman.renderCharacter(srect);
        } else {
            pacman.ripPacman(deathRect);
        }
        for(const auto& ghost: m_gameCharacters){
            ghost->renderCharacter();
        }
    }
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

void GameManager::ghostMovementWrapper(bool pause){
    for(const auto& ghost : m_gameCharacters){
        if(pause){
            ghost->setDirection(direction::NONE);
        }else{
            ghost->getMovementDirection(*level);
            ghost->moveCharacter(*level);
            ghost->collisionHandling(*level);
            ghost->isCollidingWithPacman(pacman,m_gameCharacters);
            ghost->getPacmanCoords(pacman.getCoords());
        }
    }
}
void GameManager::pacmanWrapper(bool pause){
    if(pause){
       pacman.checkMovementInput(*level);
       pacman.setDirection(direction::NONE);
    }else{
        pacman.checkMovementInput(*level);
        pacman.moveCharacter(*level);
        pacman.collisionHandling(*level);
        pacman.PickingUpPillHandler(*level);
    }
}

