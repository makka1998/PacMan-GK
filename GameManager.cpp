#include "GameManager.h"

SDL_Window *window;
SDL_Renderer *GameManager::renderer = nullptr;
Map *level;

int GameManager::startGame() {

    SDL_Init(SDL_INIT_VIDEO); // Init. SDL2
    windowLoader windowLoader;
    renderManager renderManager;

    const int FPS = 60;
    const int frameDelay = 1000 / FPS;
    Uint32 frameStart;
    int frameTime;

    // Lag et vindu med gitte settings
    window = windowLoader.createWindow("Pacman");

    // Lag en renderer til det spesifikke vinduet. Setter Hardware accelerated flag.
    renderer = renderManager.createRenderer(window);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    drawable = IMG_LoadTexture(renderer, "../Resources/Real_pacman_RIGHT.png");

    running = true;


    level = new Map("../Resources/mainLevel.txt");

    // Sett opp et "koordinatsystem" for bildet
    coords.h = 12;
    coords.w = 12;
    coords.x = 6 * 32; // Endre disse for å "flytte" bildet i vinduet/renderer
    coords.y = 9 * 32;

/* GAME LOOP START */
    while (running) {
        frameStart = SDL_GetTicks();

        chiefInspector.checkMovementInput();
        if (chiefInspector.closeGame) {
            running = false;
        }



       /* if(level->map[2]. == 30){
            int player_x = floor(coords.x / 16);
            int player_y = floor(coords.y / 16);

            if (chiefInspector.getDirection()==direction::UP &&(player_y + 1 == tile_y)) {
                //std::cout << "obstacle ahead!" << std::endl;
                chiefInspector.setDirection(chiefInspector.last_direction);
            }
        }*/
        // kan vi hente en tile utifra kordinater?



        collison();
        render();

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }
    /* GAME LOOP SLUTT */

    SDL_DestroyWindow(window);
    SDL_Quit(); // Be SDL om å rydde opp

    return EXIT_SUCCESS;
}

void GameManager::render() {
    SDL_RenderClear(renderer);
    level->drawMap();
    chiefInspector.moveCharacter(coords, drawable, renderer);
    SDL_RenderCopy(renderer, drawable, nullptr, &coords);
    SDL_RenderPresent(renderer);
}

bool GameManager::isColliding(SDL_Rect player, SDL_Rect tile) {

    //Calculate the sides of rect A
    int Player_Left = player.x;
    int Player_Right = player.x + player.w;
    int Player_Top = player.y;
    int Player_Bot = player.y + player.h;

    //Calculate the sides of rect B
    int Tile_Left = tile.x;
    int Tile_Right = tile.x + tile.w;
    int Tile_Top = tile.y;
    int Tile_Bot = tile.y + tile.h;

    //If any of the sides from Player are outside of Tile
    if (Player_Bot <= Tile_Top) { return false; }
    if (Player_Top >= Tile_Bot) { return false; }
    if (Player_Right <= Tile_Left) { return false; }
    if (Player_Left >= Tile_Right) { return false; }

    return true;
};

void GameManager::collison() {
    int pushBackDistance = 2;
    for (auto tmpMap : level->map) {

        if (isColliding(coords, tmpMap.coordinates)) {
            if (tmpMap.getTileValue() == 3) { //Vanrette
                if (chiefInspector.getDirection() == direction::DOWN) {
                    chiefInspector.setDirection(direction::NONE);
                    coords.y -= pushBackDistance;
                } else if (chiefInspector.getDirection() == direction::UP) {
                    chiefInspector.setDirection(direction::NONE);
                    coords.y += pushBackDistance;
                }
            }

            if (tmpMap.getTileValue() == 4 || tmpMap.getTileValue() == 5) {//Lodrette
                if (chiefInspector.getDirection() == direction::LEFT) {
                    chiefInspector.setDirection(direction::NONE);
                    coords.x += pushBackDistance;
                } else if (chiefInspector.getDirection() == direction::RIGHT) {
                    chiefInspector.setDirection(direction::NONE);
                    coords.x -= pushBackDistance;
                }
            }

            if (tmpMap.getTileValue() == 1 || tmpMap.getTileValue() == 11) {//Top-Venstre hjørne
                if (chiefInspector.getDirection() == direction::DOWN) {
                    chiefInspector.setDirection(direction::NONE);
                    coords.y -= pushBackDistance;
                } else if (chiefInspector.getDirection() == direction::RIGHT) {
                    chiefInspector.setDirection(direction::NONE);
                    coords.x -= pushBackDistance;
                }
            }

            if (tmpMap.getTileValue() == 2 || tmpMap.getTileValue() == 12) {//Top-Høyre hjørne
                if (chiefInspector.getDirection() == direction::DOWN) {
                    chiefInspector.setDirection(direction::NONE);
                    coords.y -= pushBackDistance;
                } else if (chiefInspector.getDirection() == direction::LEFT) {
                    chiefInspector.setDirection(direction::NONE);
                    coords.x += pushBackDistance;
                }
            }

            if (tmpMap.getTileValue() == 7 || tmpMap.getTileValue() == 13) {//Nedre-Venstre hjørne
                if (chiefInspector.getDirection() == direction::RIGHT) {
                    chiefInspector.setDirection(direction::NONE);
                    coords.x -= pushBackDistance;
                } else if (chiefInspector.getDirection() == direction::UP) {
                    chiefInspector.setDirection(direction::NONE);
                    coords.y += pushBackDistance;
                }
            }

            if (tmpMap.getTileValue() == 8 || tmpMap.getTileValue() == 14) {//Nedre-Høyre hjørne
                if (chiefInspector.getDirection() == direction::LEFT) {
                    chiefInspector.setDirection(direction::NONE);
                    coords.x += pushBackDistance;
                } else if (chiefInspector.getDirection() == direction::UP) {
                    chiefInspector.setDirection(direction::NONE);
                    coords.y += pushBackDistance;
                }
            }
            if (tmpMap.getTileValue() == 30) {//små-piller
                tmpMap.setTileValue(00);
                //std::cout << poeng << std::endl;
                poeng++;
            }


        }
    }
}