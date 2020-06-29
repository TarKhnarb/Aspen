#ifndef GAME_STATE_INVENTORY_H
#define GAME_STATE_INVENTORY_H

#include <SFML/Graphics.hpp>

#include "../BaseState.h"
#include "../EventManager.h"
#include "../Entity/Inventory.h"

class State_Inventory: public BaseState{

public:

    State_Inventory(StateManager *stateMgr);
    ~State_Inventory();

public:

    void onCreate();
    void onDestroy();

    void update(const sf::Time &time);

    void draw();

    void activate(){}
    void deactivate(){}

private:

private:

    Player &Aspen;

    sf::RectangleShape background;
};

#endif