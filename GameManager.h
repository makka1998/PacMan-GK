#ifndef PAC_MAN_GK_GAMEMANAGER_H
#define PAC_MAN_GK_GAMEMANAGER_H
#include "windowLoader.h"
#include "renderManager.h"
#include "Map.h"
#include "scoreDisplay.h"
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
    SDL_Rect srect [3];
    SDL_Rect deathRect [6];
    std::chrono::high_resolution_clock::time_point m_lastFrame = std::chrono::high_resolution_clock::now();
    static void playSound();
    int game_state = 1;
    double timer = 0;
    bool running;
    bool playedOnce = false;
    std::vector<std::shared_ptr<Ghost>> m_gameCharacters;
public:
    GameManager();
    int startGame();
    static SDL_Renderer * renderer;
    static double deltaTime;
    void calculateDeltaTime();
    void render();
    void ghostWrapper();
    void quit();
    void renderMainMenu();
    void pacmanWrapper(bool pause);
    void renderPoeng();

    void renderGameOverText(bool win);

    void playOpeningSound();

    void playMenuMusic();
};

#endif //PACMAN_GK_MASTER_GAMEMANAGER_H

