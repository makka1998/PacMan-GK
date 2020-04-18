#ifndef PAC_MAN_GK_GAMEMANAGER_H
#define PAC_MAN_GK_GAMEMANAGER_H

#include "../Characters/Pacman.h"
#include "../Characters/RedGhost.h"
#include "../Characters/BlueGhost.h"
#include "../Characters/PinkGhost.h"
#include "../Characters/OrangeGhost.h"
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
    TextManager m_textManager= TextManager("../Resources/Fonts/8-BIT.TTF", 1 * TILE_SIZE,{255, 255, 0, 255});
    SoundManager m_soundManager;

public:
    GameManager();

    static SDL_Renderer *renderer;
    static double deltaTime;

    int startGame();

    void quit();

    void render();

    void displayMainMenu();

    void calculateDeltaTime();

    void ghostWrapper();

    void pacmanWrapper();


};

#endif //PACMAN_GK_MASTER_GAMEMANAGER_H

