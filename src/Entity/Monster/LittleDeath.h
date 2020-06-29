#ifndef GAME_LITTLEDEATH_H
#define GAME_LITTLEDEATH_H

#include <cmath>

#include "Monster.h"

class LittleDeath: public Monster{

public:
    
    LittleDeath() = delete;
    LittleDeath(Character*, TextureManager*);

    ~LittleDeath();

public:

    void update(sf::Time);

    std::vector<unique_ptr<Projectile>> getProjectile();

private:

    void setProjectile();

    sf::Vector2f getDistance() const;
    void calculateDestination();

private:

    sf::Time stateTime;

    bool isMoving;

    unsigned movesNb;

    unsigned shootsNb;

    float travelled;

    sf::Vector2f destination;
};

#endif