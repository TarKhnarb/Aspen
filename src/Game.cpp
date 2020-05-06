#include "Game.h"

/***************
 * Constructor *
 ***************/
Game::Game():
        window("Aspen's Adventure", sf::Vector2u(1280,720)){

    blacksmithTexture.loadFromFile("Data/Textures/Entity/Npc/Blacksmith.png");
    blacksmith.setTexture(blacksmithTexture);
    increment = sf::Vector2f(40.f, 40.f);
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
        // TODO handleInput();
        while(elapsedTime.asSeconds() >= gameTick){
            update();
            render();

            elapsedTime -= sf::seconds(gameTick);
        }
        restartClock();
    }
}

/**********
 * Update *
 **********/
void Game::update(){
    
    window.update(); // Update window events.
    moveBlacksmith();
}

/***************
 * HandleInput *
 ***************/
 // TODO

/******************
 * MoveBlacksmith *
 ******************/
void Game::moveBlacksmith(){
    
    sf::Vector2u windSize = window.getWindowSize();
    sf::Vector2u textSize = blacksmithTexture.getSize();
    
    if((blacksmith.getPosition().x > windSize.x - textSize.x && increment.x > 0) || (blacksmith.getPosition().x < 0 && increment.x < 0))
        increment.x = - increment.x;

    if((blacksmith.getPosition().y > windSize.y - textSize.y && increment.y > 0) || (blacksmith.getPosition().y < 0 && increment.y < 0))
        increment.y = - increment.y;

    float secondElapsed = elapsedTime.asSeconds();

    blacksmith.move(increment.x * secondElapsed, increment.y * secondElapsed);

}

/**********
 * Render *
 **********/
void Game::render(){

    window.beginDraw();
    window.draw(blacksmith);
    window.endDraw();
}

/******************
 * getElapsedTime *
 ******************/
sf::Time Game::getElapsedTime(){

    return elapsedTime;
}

/****************
 * RestartClock *
 ****************/
void Game::restartClock(){

    elapsedTime += clock.restart();
}