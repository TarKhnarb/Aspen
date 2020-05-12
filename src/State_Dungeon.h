#ifndef GAME_STATE_DUNGEON_H
#define GAME_STATE_DUNGEON_H

#include <SFML/Graphics.hpp>

#include "BaseState.h"
#include "EventManager.h"
#include "Dungeon.h"

#include "Orientation.h"

class State_Dungeon : public BaseState{

public:
    
    State_Dungeon(StateManager *stateMgr);
    ~State_Dungeon();

public:

    void onCreate();
    void onDestroy();
    
    void activate();
    void deactivate();
    
    void moveCharacter(EventDetails *details);
    
    void update(const sf::Time &time);
    void draw();

    void pause(EventDetails *details);

private:

    void changeRoom(Orientation orient);

    sf::Sprite sBlacksmith;
    sf::Texture tBlacksmith;

    sf::Sprite sDungeon;
    sf::Texture tDungeon;

    sf::Vector2f increment;

    sf::Vector2i posDungeon;

    Dungeon dungeon;
};

#endif
