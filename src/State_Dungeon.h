#ifndef GAME_STATE_INTRO_H
#define GAME_STATE_INTRO_H

#include <SFML/Graphics.hpp>

#include "BaseState.h"
#include "EventManager.h"

class State_Dungeon : public BaseState{

public:
    
    State_Dungeon(StateManager*);
    ~State_Dungeon();

    void onCreate();
    void onDestroy();
    
    void activate();
    void deactivate();
    
    void moveCharacter(EventDetails *details);
    
    void update(const sf::Time &time);
    void draw();

    void pause(EventDetails *details);

private:

    sf::Sprite sBlacksmith;

    sf::Texture tBlacksmith;

    sf::Vector2f increment;
};

#endif
