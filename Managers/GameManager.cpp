#include "GameManager.h"

//kan SDL_window * være inne i startGame()?? ??????????????????????????????????????????????????????????????
SDL_Window *window;

/// Static variables
SDL_Renderer *GameManager::renderer = nullptr;
double GameManager::deltaTime;


GameManager::GameManager() {
    /// Creating and adding all ghost to m_gameCharacters.
    m_gameCharacters.push_back(std::make_shared<RedGhost>(11, 16, 13, 14, 11, 11, 9, 8));
    m_gameCharacters.push_back(std::make_shared<BlueGhost>(16, 16, 13, 14, 15, 11, 18, 8));
    m_gameCharacters.push_back(std::make_shared<PinkGhost>(11, 18, 13, 14, 9, 23, 5, 25));
    m_gameCharacters.push_back(std::make_shared<OrangeGhost>(16, 18, 12, 14, 19, 24, 22, 26));
}

int GameManager::startGame() {

    /// Initializing the SDL tools we use.
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    m_soundManager.audioInitializer();

    WindowLoader windowLoader;
    RenderManager renderManager;
    window = windowLoader.createWindow("Pacman");
    renderer = renderManager.createRenderer(window);

    SDL_Event event;
    const Uint8 *getKeyboardInput = SDL_GetKeyboardState(NULL);

    //----------------------------------------------------------------
    while (m_programRunning) {
        while (m_gameRunning) {
            SDL_PumpEvents();
            while (m_pause) {
                if (m_gameState == 1) {
                    m_soundManager.playMenuMusic();
                    m_gameState = 2;
                } else if (m_gameState == 2) {
                    calculateDeltaTime();
                    pacmanWrapper(m_pause);
                    displayMainMenu();
                }

                if (SDL_PollEvent(&event)) {
                    if (event.type == SDL_KEYDOWN) {
                        /// Unpause
                        if (event.key.keysym.sym == SDLK_RETURN) {
                            m_pause = false;
                            m_gameState = 1;

                            /// Exit game
                        } else if (event.key.keysym.sym == SDLK_ESCAPE) {
                            quit();
                            return 0;
                        }
                    } else if (event.type == SDL_QUIT) {
                        quit();
                        return 0;
                    }
                }
            }

            /// Different end conditions, either you collect all the pills, or you lose all your lives.
            if (m_pacman.getPoints() >= 240) {
                m_pacmanWon = true;
                m_gameRunning = false;
            }
            if (m_pacman.getHealth() <= 0) {
                if (m_gameState != 3) {
                    m_gameState = 3;
                    m_timer = 0;
                }
            }
            if (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    quit();
                    return 0;
                }
            }

            /// Happens once every time the game starts.
            if (m_gameState == 1) {
                if (m_playedOnce) {
                    Mix_HaltChannel(-1);
                    m_gameState = 2;
                } else {
                    m_level = new Map("../Resources/Levels/Level_layout_1.txt");
                    m_soundManager.playIntroSound(m_playedOnce);
                    m_gameState = 2;
                }
            }
            /// Main gameloop.
            if (m_gameState == 2) {
                calculateDeltaTime();
                pacmanWrapper(m_pause);
                ghostWrapper();
                render();
                if (getKeyboardInput[SDL_SCANCODE_P]) {
                    m_pause = true;
                    m_gameState = 1;
                }
            }
            if (m_gameState == 3) {
                m_timer += deltaTime;

                ///show death animation for approx 5 seconds.
                if (m_timer <= 5) {
                    SDL_RenderClear(renderer);
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
                    m_level->drawMap();
                    m_pacman.ripPacman(m_deathRect);
                    SDL_RenderPresent(renderer);
                } else {
                    m_timer = 0;
                    m_gameRunning = false;
                }
            }
        }
        m_timer += deltaTime;
        ///Show screen for approx 3 seconds.
        if (m_timer <= 30) {
            SDL_RenderClear(renderer);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
            m_level->drawMap();
            m_textManager.displayGameOverText(m_pacmanWon);
            SDL_RenderPresent(renderer);
        } else {
            break;
        }
    }
    quit();
    return 0;
}

void GameManager::quit() {
    ///SDL cleaning up and quitting.
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    TTF_Quit();
    Mix_CloseAudio();
    Mix_Quit();
    SDL_Quit();
}

void GameManager::render() {
    SDL_RenderClear(renderer);

    m_textManager.displayPoints(m_pacman.getPoints());
    m_level->drawMap();
    m_pacman.renderCharacter(m_srect);

    for (const auto &ghost: m_gameCharacters) {
        ghost->renderCharacter(m_pacman);
    }


    SDL_RenderPresent(renderer);
}

/// Displays the startup menu we render with 2 images to simulate animation on text similar to an arcade.
void GameManager::displayMainMenu() {
    m_timer += GameManager::deltaTime;
    SDL_Texture *background = IMG_LoadTexture(GameManager::renderer, "../Resources/Images/Main_menu_1.png");
    if (m_timer >= 0.5) {
        SDL_DestroyTexture(background);
        background = IMG_LoadTexture(GameManager::renderer, "../Resources/Images/Main_menu_2.png");
        if (m_timer >= 1) {
            m_timer = 0;
        }
    }
    SDL_RenderClear(renderer);
    SDL_RenderCopy(GameManager::renderer, background, nullptr, nullptr);
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(background);
}

/// Calculate delatime is used so that every computer that plays the game plays it at roughly the same speed.
void GameManager::calculateDeltaTime() {
    auto currentFrame = std::chrono::high_resolution_clock::now();
    auto deltaTimeChrono = std::chrono::duration_cast<std::chrono::duration<double>>(currentFrame - m_lastFrame);
    deltaTime = deltaTimeChrono.count();
    m_lastFrame = currentFrame;
}

/// idk
void GameManager::ghostWrapper() {
    for (const auto &ghost : m_gameCharacters) {
        ghost->getMovementDirection(*m_level);
        ghost->characterHandler(*m_level);
        ghost->isCollidingWithPacman(m_pacman, m_gameCharacters, *m_level);
    }
}

/// idk
void GameManager::pacmanWrapper(bool pause) {
    if (pause) {
        m_pacman.checkMovementInput(*m_level);
        m_pacman.setDirection(direction::NONE);
    } else {
        m_pacman.checkMovementInput(*m_level);
        m_pacman.characterHandler(*m_level);
        m_pacman.PickingUpPillHandler(*m_level);
    }
}

