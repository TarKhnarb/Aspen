#ifndef GAME_STATE_GAMEOVER_H
#define GAME_STATE_GAMEOVER_H

#include <SFML/Graphics.hpp>

#include "../BaseState.h"
#include "../EventManager.h"
#include "../Entity/Player.h"

class State_GameOver: public BaseState{

public:

    State_GameOver(StateManager *stateMgr);
    ~State_GameOver();

public:

    void onCreate();
    void onDestroy();

    void continu(EventDetails *details);

    void update(const sf::Time &time);
    void draw();

    void activate(){}
    void deactivate(){}

private:

private:

    Player &Aspen;

    sf::Text comment;
    sf::Text text;
    sf::Font font;

    float timePassed;
};

#endif