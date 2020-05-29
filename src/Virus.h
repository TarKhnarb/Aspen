#ifndef GAME_VIRUS_H
#define GAME_VIRUS_H

#include <cmath>

#include "Monster.h"

class Virus : public Monster{
    
public:
    
    Virus() = delete;
    Virus(Character*, TextureManager*);
    ~Virus();
    
public:
    
    void update(sf::Time);
    
    Projectile* getProjectile();
    
private:
    
    sf::Vector2f getDistance() const;
    void calculateDestination();
    
private:
    
    sf::Time stateTime;
    
    bool isMoving;
    
    unsigned dashesNb;
    
    sf::Vector2f destination;
    sf::Vector2f direction; // 1-unit vector
};

#endif
