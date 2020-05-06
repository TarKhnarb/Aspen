#include "Game.h"

/***************
 * Constructor *
 ***************/
Game::Game():
        window("Aspen's Adventure", sf::Vector2u(1280,720)){

    blacksmithTexture.loadFromFile("Data/Textures/Entity/Npc/Blacksmith.png");
    blacksmith.setTexture(blacksmithTexture);
    increment = sf::Vector2i(4,4);
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

        // TODO handleInput();
        update();
        render();
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

    blacksmith.setPosition(blacksmith.getPosition().x + increment.x, blacksmith.getPosition().y + increment.y);
}

/**********
 * Render *
 **********/
void Game::render(){

    window.beginDraw();
    window.draw(blacksmith);
    window.endDraw();
}

Window* Game::getWindow(){

    Window *wind = &window;
    return wind;
}