#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include <cmath>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "../EventManager.h"
#include "RoomElements/Projectile.h"
#include "Character.h"
#include "../SpriteSheet.h"
#include "Object/Statistics.h"
//#include "Inventory.h"
//#include "Dungeon.h"

class Dungeon;
class Projectile;

class Player: public Character{

public:

    Player() = delete;
    Player(TextureManager*, EventManager*);
    ~Player();

public:

    void update(sf::Time time);

    void changeRoom(Orientation orient);

    void setDungeon(Dungeon *dunge);

    void setProjectile(EventDetails*);

    Projectile* getProjectile();

    //Inventory* getInventory();
    
private:

    int returnStoi(std::istringstream &ss);
    
    void setVelocity(EventDetails*);
    
    void draw(sf::RenderTarget&, sf::RenderStates) const override;

    void animate();

private:

    SpriteSheet spriteSheet;
    
    float baseSpeed;
    
    EventManager* evtMgr;

    sf::Time timeSinceShot;
    int projHorizontal;
    int projVertical;

    Dungeon *dungeon;

    //odifications appoInventory inventory;
};

#endif
