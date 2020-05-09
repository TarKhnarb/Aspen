#ifndef GAME_STATE_INTRO_H
#define GAME_STATE_INTRO_H

#include <SFML/Graphics.hpp>

#include "BaseState.h"
#include "EventManager.h"

class State_Intro : public BaseState{

public:

    State_Intro(StateManager *stateMgr);
    ~State_Intro();

public:

    void onCreate();
    void onDestroy();

    void continu(EventDetails *details);

    void update(const sf::Time &time);

    void draw();

    void activate();
    void deactivate();

private:
    sf::Texture introTexture;
    sf::Sprite introSprite;
    sf::Text text;
    sf::Font font;
    float timePassed;
};

#endif

