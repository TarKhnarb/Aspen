#ifndef GAME_STATE_STATISTICS_H
#define GAME_STATE_STATISTICS_H

#include <SFML/Graphics.hpp>

#include "BaseState.h"
#include "EventManager.h"
#include "Player.h"

class State_Statistics: public BaseState{

public:

    State_Statistics(StateManager *stateMgr);
    ~State_Statistics();

public:

    void onCreate();
    void onDestroy();

    void update(const sf::Time &time);

    void draw();

    void activate(){}
    void deactivate(){}

private:

    Player &Aspen;

    sf::RectangleShape actualLife;
    sf::RectangleShape maxLife;

    sf::Text text; // TODO Voir si on affiche "vie_actuelle / vie_max" sur la barre de vie
    sf::Font font;

    float timePassed;
};

#endif

