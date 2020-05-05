#ifndef DUNGEON_GAME_H
#define DUNGEON_GAME_H

#include <SFML/Graphics.hpp>

class Dungeon{

public:

    Dungeon();
    ~Dungeon();

public:

    void handleInput();
    void update();
    void render();
    Window* getWindow();

private:

    void moveAspen();

private:

    Window window;
    
};

#endif