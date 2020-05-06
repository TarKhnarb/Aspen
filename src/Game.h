#ifndef GAME_GAME_H
#define GAME_GAME_H

#include "Window.h"

class Game{

public: // Conctructor / Destructor

    Game();

    ~Game();

public: // Functions

    void run();

    void handleInput(); // TODO

    void update();

    void render();

    sf::Time getElapsedTime();

    void restartClock();

private: // Functions

    void moveBlacksmith();

private: // Variable

    sf::Sprite blacksmith;

    sf::Texture blacksmithTexture;

    sf::Vector2f increment;

    Window window;

    sf::Clock clock;

    sf::Time elapsedTime;

};

#endif