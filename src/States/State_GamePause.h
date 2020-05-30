#ifndef GAME_STATE_GAMEPAUSE_H
#define GAME_STATE_GAMEPAUSE_H

#include <SFML/Graphics.hpp>

#include "../BaseState.h"
#include "../EventManager.h"

class State_GamePause : public BaseState{

public:

    State_GamePause(StateManager *stateMgr);
    ~State_GamePause();

public:

    void onCreate();
    void onDestroy();

    void unpause(EventDetails *details);
    
    void update(const sf::Time &time);
    void draw();

    void activate(){}
    void deactivate(){}

private:

    sf::Text text;
    sf::Font font;
    sf::RectangleShape rect;
};

#endif
