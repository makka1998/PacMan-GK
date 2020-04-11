#ifndef PAC_MAN_GK_GAMEMANAGER_H
#define PAC_MAN_GK_GAMEMANAGER_H
#include "windowLoader.h"
#include "renderManager.h"
#include "Map.h"
#include <iostream>
#include <chrono>
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL2/SDL_mixer.h>


class OrangeGhost;
class Pacman;

class GameManager {
private:
    SDL_Rect srect [12];
    SDL_Rect deathRect [11];
    void showGrid();
    std::chrono::high_resolution_clock::time_point m_lastFrame = std::chrono::high_resolution_clock::now();
    static void playSound();
    int game_state = 1;
    //std::vector<GameCharacter> m_gameCharacters;
public:
    int startGame();
    static SDL_Renderer * renderer;
    static double deltaTime;
    void calculateDeltaTime();
    bool running;

    void render();
};

#endif //PACMAN_GK_MASTER_GAMEMANAGER_H

