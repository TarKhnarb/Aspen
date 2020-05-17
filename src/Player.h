#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include <cmath>

#include "EventManager.h"
#include "Character.h"
#include "SpriteSheet.h"

class Player: public Character{

public:

    Player(TextureManager*, EventManager*);
    ~Player();

public:

    void update(sf::Time time);

private:
    
    void setVelocity(EventDetails*);
    
    void draw(sf::RenderTarget&, sf::RenderStates) const override;

    void animate();

private:

    SpriteSheet aspen;

    float speed;
    
    EventManager* evtMgr;
};

#endif
