#ifndef PACMAN_GK_MASTER_GHOST_H
#define PACMAN_GK_MASTER_GHOST_H

#include "GameCharacter.h"
#include "Pacman.h"
class Ghost : public GameCharacter {
protected:
    SDL_Texture* m_texture;
    SDL_Rect m_pacmanPos;

    int m_startingPosition [2];
    int m_respawnPosition [2];
    int m_distanceToTarget [2];
    int m_RNG = 1;
    double m_timer = 0;
    bool m_startingDestinationReached = false;

    std::vector<bool> wayPointsReached;
    std::vector<int> wayPoints;

public:
    Ghost(int xs, int ys, int xr, int yr, int wp1, int wp2, int wp3, int wp4, int wp5, int wp6);

    void setDistanceToTarget(int pacmanPos []);

    virtual void getMovementDirection(Map &map){};

    virtual void renderCharacter(Pacman & pMan);

    void isCollidingWithPacman(Pacman & pMan, const std::vector<std::shared_ptr<Ghost>>& gameCharacters, Map &map);

    void moveToRespawnPos();

    void playDeathSound();

    void playEatenSound();

    void wanderRandom(Map &map);
};


#endif //PACMAN_GK_MASTER_GHOST_H
