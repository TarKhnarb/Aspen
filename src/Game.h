#ifndef GAME_GAME_H
#define GAME_GAME_H

#include "Window.h"
#include "EventManager.h"
#include "StateManager.h"
#include "TextureManager.h"
#include "SharedContext.h"
#include "Entity/Player.h"

class Game{

public: // Conctructor / Destructor

    Game();

    ~Game();

public: // Functions

    void run();

private: // Functions

    void processEvent();

    void update(sf::Time);

    void render();

    void restartClock();

    void moveBlacksmith(EventDetails *details);

    void lateUpdate();

private: // Variable

    Window window;

    sf::Clock clock;

    sf::Time elapsedTime;
    
    TextureManager textureManager;
    
    StateManager stateManager;

    SharedContext context;
    
    Player aspen;
};

#endif
