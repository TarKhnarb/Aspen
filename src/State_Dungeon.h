#ifndef GAME_STATE_DUNGEON_H
#define GAME_STATE_DUNGEON_H

#include <SFML/Graphics.hpp>

#include "BaseState.h"
#include "EventManager.h"
#include "Dungeon.h"
#include "Orientation.h"
#include "Player.h"

class State_Dungeon : public BaseState{

public:
    
    State_Dungeon(StateManager *stateMgr);
    ~State_Dungeon();

public:

    void onCreate();
    void onDestroy();
    
    void activate();
    void deactivate();
    
    void update(const sf::Time &time);
    void draw();

    void pause(EventDetails *details);

private:

    void centerPlayer();

private:

    Dungeon dungeon;
    
    Player player;
};

#endif
