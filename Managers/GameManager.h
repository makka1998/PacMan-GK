#ifndef PAC_MAN_GK_GAMEMANAGER_H
#define PAC_MAN_GK_GAMEMANAGER_H

#include "../Characters/Pacman.h"
#include "../Characters/Ghosts/RedGhost.h"
#include "../Characters/Ghosts/BlueGhost.h"
#include "../Characters/Ghosts/PinkGhost.h"
#include "../Characters/Ghosts/OrangeGhost.h"
#include "WindowLoader.h"
#include "RenderManager.h"
#include "TextManager.h"
#include "../Map.h"
#include <iostream>
#include <chrono>
#include <SDL.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <memory>
#include "TextManager.h"
#include "SoundManager.h"

///Forward declarations of classes
class Ghost;

class Pacman;

class GameCharacter;

class GameManager {
private:
    SDL_Window *m_window;
    ///Manager objects
    WindowLoader m_windowLoader;
    RenderManager m_renderManager;
    TextManager m_textManager = TextManager("../Resources/Fonts/8-BIT.TTF", 1 * TILE_SIZE, {255, 255, 0, 255});
    SoundManager m_soundManager;
    std::chrono::high_resolution_clock::time_point m_lastFrame = std::chrono::high_resolution_clock::now();
    int m_gameState = 1;
    int m_mapChoice = 1;
    double m_timer = 0;
    bool m_gameRunning = true;
    bool m_playedOnce = false;
    bool m_pause = true;
    bool m_pacmanWon = false;
    std::vector<std::shared_ptr<Ghost>> m_ghosts;
    Pacman m_pacman;
    Map *m_level;


public:
    /// Constructor
    GameManager();

    /// Static variables
    static double deltaTime;
    static SDL_Renderer *renderer;

    /// Public functions
    int startGame();

    void quit();

    void render();

    void displayMainMenu();

    void calculateDeltaTime();

    void ghostWrapper();

    void pacmanWrapper();

    void pausedState(SDL_Event event);

    void gameOverState();

    void gamePlayingState(SDL_Event event);

    void loadGame();
};

#endif //PACMAN_GK_MASTER_GAMEMANAGER_H

