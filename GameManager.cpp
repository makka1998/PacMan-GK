#include "GameManager.h"
#include "Pacman.h"
#include "RedGhost.h"
#include "BlueGhost.h"
#include "PinkGhost.h"
#include "OrangeGhost.h"
#include "scoreDisplay.h"
#include <string>

SDL_Window *window;
SDL_Renderer *GameManager::renderer = nullptr;
double GameManager::deltaTime;
Map *level;
Pacman pacman;

GameManager::GameManager() {

    SDL_Rect *pacmanCoords = pacman.getCoords();
    m_gameCharacters.push_back(std::make_shared<RedGhost>(12, 16, 10, 11, 15, 12, 11, 9, 8, 7));
    m_gameCharacters.push_back(std::make_shared<BlueGhost>(17, 16, 19, 11, 13, 12, 17, 9, 20, 7));
    m_gameCharacters.push_back(std::make_shared<PinkGhost>(12, 18, 10, 14, 15, 12, 8, 24, 5, 26));
    m_gameCharacters.push_back(std::make_shared<OrangeGhost>(17, 18, 19, 14, 13, 12, 20, 24, 23, 26));
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
    const Uint8 *getKeyboardInput = SDL_GetKeyboardState(NULL);


    running = true;
    bool pause = true;
    bool programRunning = true;
    bool pacmanWin = false;

    //calculateDeltaTime();
    //----------------------------------------------------------------
    while (programRunning) {
        while (running) {
            while (pause) {
                if (game_state == 1) {
                    playMenuMusic();
                    game_state = 2;
                } else if (game_state == 2) {
                    //Mix_HaltChannel(-1);
                    calculateDeltaTime();
                    pacmanWrapper(pause);
                    renderMainMenu();
                }

                if (getKeyboardInput[SDL_SCANCODE_RETURN]) {
                    pause = false;
                    game_state = 1;
                }
                if (getKeyboardInput[SDL_SCANCODE_ESCAPE]) {
                    pause = false;
                    running = false;
                }
            }
                if (pacman.getPoints() >= 240) {
                    pacmanWin = true;
                    running = false;
                }
                if (pacman.getHealth() <= 0) {
                    if (game_state != 3) {
                    game_state = 3;
                    timer = 0;
                }
                }

            if (game_state == 1) {
                level = new Map("../Resources/mainLevel.txt");
                //Opening sound
                playOpeningSound();
                game_state = 2;
            }
            if (game_state == 2) {
                calculateDeltaTime();
                pacmanWrapper(pause);
                ghostWrapper();
                render();
                if (getKeyboardInput[SDL_SCANCODE_P]) {
                    pause = true;
                    game_state = 1;
                }
            }
            if (game_state == 3) {
                timer += deltaTime;
                if (timer <= 5) {
                    //std::cout << timer;
                    SDL_RenderClear(renderer);
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
                    level->drawMap();
                    pacman.ripPacman(deathRect);
                    SDL_RenderPresent(renderer);
                } else {
                timer = 0;
                running = false;}
            }
        }
            if (getKeyboardInput[SDL_SCANCODE_ESCAPE]) {
                break;
            }
            timer += deltaTime;
            //show screen for 3 seconds.
            if (timer <= 30) {
                SDL_RenderClear(renderer);
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
                level->drawMap();
                renderGameOverText(pacmanWin);
                SDL_RenderPresent(renderer);
            } else {
                break;
            }
        }
        quit();
        return EXIT_SUCCESS;
}

void GameManager::quit() {
    SDL_DestroyWindow(window);
    TTF_Quit();
    Mix_Quit();
    SDL_Quit(); // Be SDL om å rydde opp
};

void GameManager::render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);

    renderPoeng();
    level->drawMap();
    //showGrid();
    pacman.renderCharacter(srect);

    for (const auto &ghost: m_gameCharacters) {
        ghost->renderCharacter(pacman);
    }

    SDL_RenderPresent(renderer);
}

void GameManager::playSound() {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
    }
}

void GameManager::playOpeningSound() {
    if(Mix_Playing(6)) {
        Mix_HaltChannel(6);
    }
    auto openingSound = Mix_LoadWAV("../Resources/pacman_beginning.wav");
    if (openingSound == nullptr) {
        printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
    }
    Mix_Volume(-1, 5);
    Mix_PlayChannel(6, openingSound, 0);
}
void GameManager::playMenuMusic() {
    if(Mix_Playing(6)) {
        Mix_HaltChannel(6);
    }
    auto menuMusic = Mix_LoadWAV("../Resources/pacman_menumusic.wav");
    if (menuMusic == nullptr) {
        printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
    }
    Mix_Volume(-1, 5);
    Mix_PlayChannel(6, menuMusic, -1);
}

void GameManager::renderMainMenu() {
    timer += GameManager::deltaTime;
    SDL_Texture *background = IMG_LoadTexture(GameManager::renderer, "../Resources/Old_Tilesets/mainMenu_1.png");
    if (timer >= 0.5) {
        SDL_DestroyTexture(background);
        background = IMG_LoadTexture(GameManager::renderer, "../Resources/Old_Tilesets/mainMenu_2.png");
        if (timer >= 1) {
            timer = 0;
        }
    }
    SDL_RenderClear(renderer);
    SDL_RenderCopy(GameManager::renderer, background, nullptr, nullptr);
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(background);
}

void GameManager::renderPoeng() {
    std::string poeng = std::to_string(pacman.getPoints());
    scoreDisplay score(GameManager::renderer, "../Resources/Old_Tilesets/Arial.ttf", 1 * TILE_SIZE, "Points: " + poeng,
                       {255, 255, 255, 255});
    score.display(13 * TILE_SIZE, 1.5 * TILE_SIZE, renderer);
}

void GameManager::renderGameOverText(bool win) {
    scoreDisplay text(GameManager::renderer, "../Resources/Old_Tilesets/8-BIT WONDER.TTF", 1 * TILE_SIZE, "GAME OVER",
                      {255, 255, 0, 255});
    text.display(11 * TILE_SIZE, 26 * TILE_SIZE, renderer);
    std::string gameResult = "YOU LOSE";
    if (win) {
        gameResult = "YOU WIN";
    }
    scoreDisplay gameCondtitionText(GameManager::renderer, "../Resources/Old_Tilesets/8-BIT WONDER.TTF", 1 * TILE_SIZE,
                                    gameResult, {255, 255, 0, 255});
    gameCondtitionText.display(11.5 * TILE_SIZE, 35 * TILE_SIZE, renderer);

}

void GameManager::showGrid() {
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

void GameManager::ghostWrapper() {
    for (const auto &ghost : m_gameCharacters) {
        ghost->getMovementDirection(*level);
        ghost->moveCharacter(*level);
        ghost->collisionHandling(*level);
        ghost->isCollidingWithPacman(pacman, m_gameCharacters, *level);
    }
}

void GameManager::pacmanWrapper(bool pause) {
    if (pause) {
        pacman.checkMovementInput(*level);
        pacman.setDirection(direction::NONE);
    } else {
        pacman.checkMovementInput(*level);
        pacman.moveCharacter(*level);
        pacman.collisionHandling(*level);
        pacman.PickingUpPillHandler(*level);
    }
}

