#include "Game.h"

/***************
 * Constructor *
 ***************/
Game::Game():
        window("Aspen's Adventure", sf::Vector2u(1280,720)),
        stateManager(&context){

    context.wind = &window;
    context.eventManager = window.getEventManager();
    context.textureManager = &textureManager;
    
    stateManager.switchTo(StateType::Map);
}

/**************
 * Destructor *
 **************/
Game::~Game(){}


/*******
 * run *
 *******/
void Game::run(){

    while(!window.isClose()){

        sf::Time gameTick = sf::seconds(1.f/60.f);
        processEvent();

        if(elapsedTime >= gameTick){

            update(gameTick);
            lateUpdate();
        }
        
        render();
        restartClock();
    }
}

/**********
 * Update *
 **********/
void Game::update(sf::Time dt){
    
    window.update(); // Update window events.
    stateManager.update(dt);
}

/****************
 * ProcessEvent *
 ****************/
void Game::processEvent(){

    window.processEvents();
}

/**********
 * Render *
 **********/
void Game::render(){

    window.beginDraw();
    stateManager.draw();
    window.endDraw();
}

/****************
 * RestartClock *
 ****************/
void Game::restartClock(){

    elapsedTime += clock.restart();
}

/**************
 * LateUpdate *
 **************/
void Game::lateUpdate(){
    stateManager.processRequests();
    
    elapsedTime = sf::Time::Zero;
    restartClock();
}
