#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include <cmath>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "EventManager.h"
#include "Character.h"
#include "SpriteSheet.h"
#include "Statistics.h"

class Player: public Character{

public:

    Player(TextureManager*, EventManager*);
    ~Player();

public:

    void update(sf::Time time);

    void changeRoom(Orientation orient);
    
    void setBaseSpeed(float);

    Statistics* getStats();
    
private:

    int returnStoi(std::istringstream &ss);
    
    void setVelocity(EventDetails*);
    
    void draw(sf::RenderTarget&, sf::RenderStates) const override;

    void animate();

private:

    SpriteSheet spritesheet;
    
    Statistics stats;
    
    float baseSpeed;
    
    EventManager* evtMgr;
};

#endif
