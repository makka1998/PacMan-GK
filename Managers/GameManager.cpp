#include "GameManager.h"

/// Initialize Static variables
SDL_Renderer *GameManager::renderer = nullptr;
double GameManager::deltaTime;

/**
 *  Constructor.
 *  We create and add all ghosts to the ghosts vector with predefined waypoints and X;Y Coordinates.
 */
GameManager::GameManager() {
    /// Creating and adding all ghost to our ghosts vector.
    m_ghosts.push_back(std::make_shared<RedGhost>(11, 16, 13, 14, 11, 11, 9, 8));
    m_ghosts.push_back(std::make_shared<BlueGhost>(16, 16, 13, 14, 15, 11, 18, 8));
    m_ghosts.push_back(std::make_shared<PinkGhost>(11, 18, 13, 14, 9, 23, 5, 25));
    m_ghosts.push_back(std::make_shared<OrangeGhost>(16, 18, 12, 14, 19, 24, 22, 26));
}

/**
 *  startGame is our main function that will hold our gameloop and initilize all libraries.
 * it's here we are creating our window and renderer and keeping track of which gameState the game is in.
 *  startGame() is called in main.cpp.
 * if startGame() is done, the game quits.
*/
int GameManager::startGame() {

    /// Initializing the SDL tools we use.
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    m_soundManager.audioInitializer();

    ///Creating window and renderer
    window = windowLoader.createWindow("Pacman");
    renderer = renderManager.createRenderer(window);
    SDL_Event event;

    //----------------------------------------------------------------
    while (m_gameRunning) {
        SDL_PumpEvents();

        ///Paused Game
        while (m_pause) {
            pausedState(event);
        }

        /// Happens once every time the game starts.
        if (m_gameState == 1) {
            loadGame();
        }

        /// Main gameloop.
        if (m_gameState == 2) {
            gamePlayingState(event);
        }

        /// Game over!
        if (m_gameState == 3) {
            gameOverState();
        }

        /// Exit Window listener
        if (SDL_PollEvent(&event) && event.type == SDL_QUIT){
            break;
        }
    }
    quit();
    return 0;
}

/**
 *  This is an quit all function. An wrapper for all free/close/destroy and etc..
 *  only use this when closing game and quitting application.
 */
void GameManager::quit() {
    ///SDL cleaning up and quitting.
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    TTF_Quit();
    Mix_CloseAudio();
    Mix_Quit();
    Mix_CloseAudio();
    SDL_Quit();
}

/**
 *  Wrapper function for all rendering functions
 */
void GameManager::render() {
    SDL_RenderClear(renderer);

    m_textManager.displayPoints(m_pacman.getPoints());
    m_level->drawMap();
    m_pacman.renderCharacter();

    for (const auto &ghost: m_ghosts) {
        ghost->renderCharacter(m_pacman);
    }

    SDL_RenderPresent(renderer);
}

/**
 * Loading in map and playing intro sound
 */
void GameManager::loadGame() {
    if (m_playedOnce) {
        Mix_HaltChannel(-1);
        m_gameState = 2;
    } else {
        m_level = new Map("../Resources/Levels/Level_layout_1.txt");
        m_soundManager.playIntroSound(m_playedOnce);
        m_gameState = 2;
    }
}

/**
 * if the game is paused we will display mainMenu and play MenyMusic.
 * checking for key events to unpause or quit the game.
 */
void GameManager::pausedState(SDL_Event event) {
    if (m_gameState == 1) {
        m_soundManager.playMenuMusic();
        m_gameState = 2;
    } else if (m_gameState == 2) {
        calculateDeltaTime();
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
                m_pause = false;
                m_gameRunning = false;
            }
        }
    }
}

/**
 * if the player has collected all pills or lost all lives gameOverState runs
 *  it will play pacmanDeathAnimation and show game over screen and quit after 3 seconds.
 */
void GameManager::gameOverState() {
    m_timer += deltaTime;
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    m_level->drawMap();
    if (!m_pacmanWon && m_timer <= 5) {
        m_pacman.pacmanDeathAnimation();
        SDL_RenderPresent(renderer);
    } else if (m_timer <= 20) {
        m_textManager.displayGameOverText(m_pacmanWon);
        SDL_RenderPresent(renderer);
    } else {
        m_gameRunning = false;
    }
}

/**
 * This is the content of the game loop. it will render map, and run all player and ghosts functions.
 * it will also check for the win/lose condtitions.
 * also checking for keyevents to pause the game.
 */
void GameManager::gamePlayingState(SDL_Event event) {
    Mix_HaltMusic();
    calculateDeltaTime();
    pacmanWrapper();
    ghostWrapper();
    render();

    /// Different end conditions, either you collect all the pills, or you lose all your lives.
    if (m_pacman.getPoints() >= 20) {
        m_pacmanWon = true;
        m_gameState = 3;
        m_timer = 0;
    }
    if (m_pacman.getHealth() <= 0) {
            m_gameState = 3;
            m_timer = 0;
    }

    if (SDL_PollEvent(&event)) {
        if (event.type == SDL_KEYDOWN) {
            /// Unpause
            if (event.key.keysym.sym == SDLK_p) {
                m_pause = true;
                m_gameState = 1;
            }
        }
    }
}

/**
 * Displays the startup menu. We render 2 similare images to simulate animation on text similar to an arcade.
 */
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

/**
 * Calculate delatime is used so that every computer that plays the game plays it at roughly the same speed.
 */
void GameManager::calculateDeltaTime() {
    auto currentFrame = std::chrono::high_resolution_clock::now();
    auto deltaTimeChrono = std::chrono::duration_cast<std::chrono::duration<double>>(currentFrame - m_lastFrame);
    deltaTime = deltaTimeChrono.count();
    m_lastFrame = currentFrame;
}

/**
 *  Wraps all ghost related funtions into one ghostWrapper. This is done for practicality.
 */
void GameManager::ghostWrapper() {
    for (const auto &ghost : m_ghosts) {
        ghost->getMovementDirection(*m_level);
        ghost->characterHandler(*m_level);
        ghost->pacmanGhostCollisionManager(m_pacman, m_ghosts, *m_level);
    }
}

/**
 *  Wraps all pacman related funtions into one pacmanWrapper. This is done for practicality.
 */
void GameManager::pacmanWrapper() {
    m_pacman.setDirection(*m_level);
    m_pacman.characterHandler(*m_level);
    m_pacman.pickingUpPillHandler(*m_level);
}
