
#ifndef PACMAN_GK_MASTER_GAMECHARACTER_H
#define PACMAN_GK_MASTER_GAMECHARACTER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <memory>
#include "../Map.h"
#include "../Managers/CollisionManager.h"
#include "../Managers/MovementManager.h"
#include "../Managers/SoundManager.h"



class GameCharacter {
protected:
    CollisionManager m_collisionManager;
    MovementManager m_movementManager;
    direction m_direction = direction::NONE;
    SoundManager m_soundManager;

    SDL_Rect m_coordinates;
    SDL_Texture *m_texture;
    ///Animation number is used to keep track of which frame of the animation we are on.
    int m_animationNumber;
    int m_speed;
    double m_timer = 0;

public:

    GameCharacter(int xs, int ys, int speed);

    void characterHandler(Map &map);

    virtual void renderCharacter() {};

    virtual void moveToStartPos() {};
};


#endif //PACMAN_GK_MASTER_GAMECHARACTER_H
