#ifndef GAME_GAME_H
#define GAME_GAME_H

#include "Window.h"
#include "EventManager.h"

class Game{

public: // Conctructor / Destructor

    Game();

    ~Game();

public: // Functions

    void run();

private: // Functions

    void processEvent();

    void update();

    void render();

    sf::Time getElapsedTime();

    void restartClock();

    void moveBlacksmith(EventDetails *details);

private: // Variable

    sf::Sprite blacksmith;

    sf::Texture blacksmithTexture;

    sf::Vector2f increment;

    Window window;

    sf::Clock clock;

    sf::Time elapsedTime;
};

#endif