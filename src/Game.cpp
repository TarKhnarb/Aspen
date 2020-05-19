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

        float gameTick = 1.f/60.f;
        processEvent();

        while(elapsedTime.asSeconds() >= gameTick){

            processEvent();
            update();
            lateUpdate();

            elapsedTime -= sf::seconds(gameTick);
        }
        render();
        restartClock();
    }
}

/**********
 * Update *
 **********/
void Game::update(){
    
    window.update(); // Update window events.
    stateManager.update(elapsedTime);
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

/******************
 * getElapsedTime *
 ******************/
sf::Time Game::getElapsedTime() const{

    return elapsedTime;
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
    restartClock();
}
