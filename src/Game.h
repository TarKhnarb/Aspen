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

    Window* getWindow();

private: // Functions

    void moveBlacksmith();

private: // Variable

    sf::Sprite blacksmith;

    sf::Texture blacksmithTexture;

    sf::Vector2i increment;

    Window window;

};

#endif