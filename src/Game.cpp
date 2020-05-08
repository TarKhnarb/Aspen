#include "Game.h"

/***************
 * Constructor *
 ***************/
Game::Game():
        window("Aspen's Adventure", sf::Vector2u(1280,720)){

    blacksmithTexture.loadFromFile("Data/Textures/Entity/Npc/Blacksmith.png");
    blacksmith.setTexture(blacksmithTexture);
    increment = sf::Vector2f(40.f, 40.f);

    window.getEventManager()->addCallback("MoveUp", &Game::moveBlacksmith, this);
    window.getEventManager()->addCallback("MoveRight", &Game::moveBlacksmith, this);
    window.getEventManager()->addCallback("MoveDown", &Game::moveBlacksmith, this);
    window.getEventManager()->addCallback("MoveLeft", &Game::moveBlacksmith, this);
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
}

/****************
 * ProcessEvent *
 ****************/
void Game::processEvent(){

    window.processEvents();
}

/******************
 * MoveBlacksmith *
 ******************/
void Game::moveBlacksmith(EventDetails *details){

    /* particle in a case
    sf::Vector2u windSize = window.getWindowSize();
    sf::Vector2u textSize = blacksmithTexture.getSize();


    if((blacksmith.getPosition().x > windSize.x - textSize.x && increment.x > 0) || (blacksmith.getPosition().x < 0 && increment.x < 0))
        increment.x = - increment.x;

    if((blacksmith.getPosition().y > windSize.y - textSize.y && increment.y > 0) || (blacksmith.getPosition().y < 0 && increment.y < 0))
        increment.y = - increment.y;
    */

    sf::Vector2f direction;

    if(details->name == "MoveUp"){

        direction = sf::Vector2f(0.f, -increment.y);
    }
    if(details->name == "MoveRight"){

        direction = sf::Vector2f(increment.x, 0.f);
    }
    if(details->name == "MoveDown"){

        direction = sf::Vector2f(0.f, increment.y);
    }
    if(details->name == "MoveLeft"){

        direction = sf::Vector2f(-increment.x, 0.f);
    }

    float secondElapsed = elapsedTime.asSeconds();

    blacksmith.move(direction.x * secondElapsed, direction.y * secondElapsed);

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