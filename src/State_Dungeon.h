#ifndef GAME_STATE_INTRO_H
#define GAME_STATE_INTRO_H

#include <SFML/Graphics.hpp>

#include "BaseState.h"
#include "Window.h"

class State_Dungeon : public BaseState{

public:

    void onCreate();
    void onDestroy();

    void update(EventDetails *details);

    void draw();

    void pause(EventDetails *details);

private:

    sf::Sprite sBlacksmith;

    sf::Texture tBlacksmith;

    sf::Vector2f increment;
};

#endif