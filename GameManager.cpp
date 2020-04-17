#include "GameManager.h"
#include "Pacman.h"
#include "RedGhost.h"
#include "BlueGhost.h"
#include "PinkGhost.h"
#include "OrangeGhost.h"

//kan SDL_window * være inne i startGame()??
SDL_Window *window;

//static variables
SDL_Renderer *GameManager::renderer = nullptr;
double GameManager::deltaTime;
Map *level;
Pacman pacman;

GameManager::GameManager() {
    //Creating and adding all ghost to m_gameCharacters.
    m_gameCharacters.push_back(std::make_shared<RedGhost>(11, 16, 9, 11, 13, 14, 11, 11, 9, 8));
    m_gameCharacters.push_back(std::make_shared<BlueGhost>(16, 16, 18, 11, 13, 14, 15, 11, 18, 8));
    m_gameCharacters.push_back(std::make_shared<PinkGhost>(11, 18, 9, 14, 13, 14, 9, 23, 5, 25));
    m_gameCharacters.push_back(std::make_shared<OrangeGhost>(16, 18, 18, 14, 12, 14, 19, 24, 22, 26));
}

int GameManager::startGame() {

    //initialize all libraries
    SDL_Init(SDL_INIT_VIDEO); // Init. SDL2
    TTF_Init();
    //Mix_init(); ?? add this? instead of playSound()?

    windowLoader windowLoader;
    renderManager renderManager;
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
                    calculateDeltaTime();
                    pacmanWrapper(pause);
                    renderMainMenu();
                }

                //exit game
                if (getKeyboardInput[SDL_SCANCODE_RETURN]) {
                    pause = false;
                    game_state = 1;
                }

                //unpause
                if (getKeyboardInput[SDL_SCANCODE_ESCAPE]) {
                    pause = false;
                    running = false;
                }
            }

            //end game conditions for pacman health
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

            //happens once every time the game starts
            if (game_state == 1) {
                if(playedOnce){
                    Mix_HaltChannel(-1);
                    game_state = 2;
                } else {
                    level = new Map("../Resources/Levels/Level_layout_1.txt");
                    playOpeningSound();
                    game_state = 2;
                }
            }
            //main game-play
            if (game_state == 2) {
                //make this a function named main_gameplay or just game_state 2=?
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
                //make this a function named death? or game_state 3?
                timer += deltaTime;
                //show death animation for approx 5 seconds.
                if (timer <= 5) {
                    SDL_RenderClear(renderer);
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
                    level->drawMap();
                    pacman.ripPacman(deathRect);
                    SDL_RenderPresent(renderer);
                } else {
                    timer = 0;
                    running = false;
                }
            }
        }
        //you can quit the game if you dont want to wait approx 3 seconds in the game over scenario.
        if (getKeyboardInput[SDL_SCANCODE_ESCAPE]) {
            break;
        }
        timer += deltaTime;
        //show screen for approx 3 seconds.
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
    return 0;
}

void GameManager::quit() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    TTF_Quit();
    Mix_Quit();
    SDL_Quit(); // Be SDL om å rydde opp
};

void GameManager::render() {
    SDL_RenderClear(renderer);

    renderPoeng();
    level->drawMap();
    pacman.renderCharacter(srect);

    for (const auto &ghost: m_gameCharacters) {
        ghost->renderCharacter(pacman);
    }

    SDL_RenderPresent(renderer);
}

//name change?
void GameManager::playSound() {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer initialization failed! SDL_mixer Error: %s\n", Mix_GetError());
    }
}

void GameManager::playOpeningSound() {
    if (Mix_Playing(6)) {
        Mix_HaltChannel(6);
    }
    auto openingSound = Mix_LoadWAV("../Resources/Sounds/pacman_intro_sound.wav");
    if (openingSound == nullptr) {
        printf("Failed to load intro sound effect! SDL_mixer Error: %s\n", Mix_GetError());
    }
    playedOnce = true;
    Mix_PlayChannel(6, openingSound, 0);
}

void GameManager::playMenuMusic() {
    if (Mix_Playing(-1)) {
        Mix_HaltChannel(-1);
    }
    auto menuMusic = Mix_LoadWAV("../Resources/Sounds/pacman_menu_sound.wav");
    if (menuMusic == nullptr) {
        printf("Failed to load menu sound effect! SDL_mixer Error: %s\n", Mix_GetError());
    }
    Mix_Volume(-1, 5);
    Mix_PlayChannel(6, menuMusic, -1);
}

void GameManager::renderMainMenu() {
    timer += GameManager::deltaTime;
    SDL_Texture *background = IMG_LoadTexture(GameManager::renderer, "../Resources/Images/Main_menu_1.png");
    if (timer >= 0.5) {
        SDL_DestroyTexture(background);
        background = IMG_LoadTexture(GameManager::renderer, "../Resources/Images/Main_menu_2.png");
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
    scoreDisplay score(GameManager::renderer, "../Resources/Fonts/8-BIT.TTF", 1 * TILE_SIZE,
                       "Points " + poeng, {255, 255, 0, 255});
    score.display(10.2 * TILE_SIZE, 1.5 * TILE_SIZE, renderer);
}

void GameManager::renderGameOverText(bool win) {
    scoreDisplay text(GameManager::renderer, "../Resources/Fonts/8-BIT.TTF", 1 * TILE_SIZE, "GAME OVER",
                      {255, 255, 0, 255});
    text.display(9.5 * TILE_SIZE, 14 * TILE_SIZE, renderer);
    std::string gameResult = "YOU LOSE";
    if (win) {
        gameResult = "YOU WIN";
    }
    scoreDisplay gameCondtitionText(GameManager::renderer, "../Resources/Fonts/8-BIT.TTF", 1 * TILE_SIZE,
                                    gameResult, {255, 255, 0, 255});
    gameCondtitionText.display(10.25 * TILE_SIZE, 20 * TILE_SIZE, renderer);

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
        ghost->moveCharacter(140);
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
        pacman.moveCharacter(200);
        pacman.collisionHandling(*level);
        pacman.PickingUpPillHandler(*level);
    }
}

