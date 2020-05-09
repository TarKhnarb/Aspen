#ifndef GAME_STATE_GAMEPAUSE_H
#define GAME_STATE_GAMEPAUSE_H

#include <SFML/Graphics.hpp>

#include "BaseState.h"
#include "Window.h"

class State_GamePause : public BaseState{

public:

    void onCreate();
    void onDestroy();

    void unpause(EventDetails *details);

    void draw();

private:

    sf::Text text;
    sf::Font font;
    sf::RectangleShape rect;
};

#endif