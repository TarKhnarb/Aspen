#ifndef GAME_STATE_MAP_H
#define GAME_STATE_MAP_H

#include <SFML/Graphics.hpp>

#include "BaseState.h"
#include "EventManager.h"
#include "Map.h"
#include "Player.h"

class State_Map : public BaseState{

public:

    State_Map(StateManager*);
    ~State_Map();

public:

    void onCreate();
    void onDestroy();

    void activate();
    void deactivate();

    void update(const sf::Time &time);
    void draw();

private:

    void spawnPointPlayer();

    void setViewOnPlayer();

private:

    Map map;
    
    Player &Aspen;

};

#endif
