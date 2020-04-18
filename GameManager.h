#ifndef PAC_MAN_GK_GAMEMANAGER_H
#define PAC_MAN_GK_GAMEMANAGER_H

#include "Pacman.h"
#include "RedGhost.h"
#include "BlueGhost.h"
#include "PinkGhost.h"
#include "OrangeGhost.h"
#include "WindowLoader.h"
#include "RenderManager.h"
#include "scoreDisplay.h"
#include "Map.h"
#include <iostream>
#include <chrono>
#include <SDL.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <memory>

//characters include
class Ghost;

class Pacman;

class GameCharacter;

class GameManager {
private:
    SDL_Rect m_srect[3];
    SDL_Rect m_deathRect[6];
    std::chrono::high_resolution_clock::time_point m_lastFrame = std::chrono::high_resolution_clock::now();
    int m_gameState = 1;
    double m_timer = 0;
    bool m_gameRunning = true;
    bool m_playedOnce = false;
    bool m_pause = true;
    bool m_programRunning = true;
    bool m_pacmanWon = false;
    std::vector<std::shared_ptr<Ghost>> m_gameCharacters;
    Pacman m_pacman;
    Map * m_level;

    static void audioInitializer();

    void playMenuMusic();

    void playOpeningSound();

public:
    GameManager();

    static SDL_Renderer *renderer;
    static double deltaTime;

    int startGame();

    void quit();

    void render();

    void displayMainMenu();

    void displayPoints();

    void displayGameOverText(bool win);

    void calculateDeltaTime();

    void ghostWrapper();

    void pacmanWrapper();


};

#endif //PACMAN_GK_MASTER_GAMEMANAGER_H

