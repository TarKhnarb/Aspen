#include "State_Dungeon.h"
#include "StateManager.h"

/************
 * OnCreate *
 ************/
void State_Dungeon::onCreate(){

    sf::Vector2u windowSize = stateMgr->getContext()->wind->getWindow()->getSize();

    tBlacksmith.loadFromFile("Data/Textures/Entity/Npc/Blacksmith.png");
    sBlacksmith.setTexture(tBlacksmith);
    sBlacksmith.setPosition((windowSize.x - tBlacksmith.getSize().x)/2.f, (windowSize.y - tBlacksmith.getSize().y)/2.f);

    increment = sf::Vector2f(80.f, 80.f);

    EventManager *evMgr = stateMgr->getContext()->eventManager;

    evMgr->addCallback(StateType::Dungeon, "MoveUp", &State_Dungeon::update, this);
    evMgr->addCallback(StateType::Dungeon, "MoveRight", &State_Dungeon::update, this);
    evMgr->addCallback(StateType::Dungeon, "MoveDown", &State_Dungeon::update, this);
    evMgr->addCallback(StateType::Dungeon, "MoveLeft", &State_Dungeon::update, this);
    evMgr->addCallback(StateType::Dungeon, "GamePause", &State_Dungeon::pause, this);
    evMgr->addCallback(StateType::Dungeon,"Dungeon",&State_Dungeon::update,this);

}

/*************
 * OnDestroy *
 *************/
void State_Dungeon::onDestroy(){

    EventManager *evMgr = stateMgr->getContext()->eventManager;

    evMgr->removeCallback(StateType::Dungeon,"MoveUp");
    evMgr->removeCallback(StateType::Dungeon,"MoveRight");
    evMgr->removeCallback(StateType::Dungeon,"MoveDown");
    evMgr->removeCallback(StateType::Dungeon,"MoveLeft");
    evMgr->removeCallback(StateType::Dungeon,"GamePause");
}

/**********
 * Update *
 **********/
void State_Dungeon::update(EventDetails *details){

    /* particle in a case
    sf::Vector2u windSize = window.getWindowSize();
    sf::Vector2u textSize = blacksmithTexture.getSize();


    if((blacksmith.getPosition().x > windSize.x - textSize.x && increment.x > 0) || (blacksmith.getPosition().x < 0 && increment.x < 0))
        increment.x = - increment.x;

    if((blacksmith.getPosition().y > windSize.y - textSize.y && increment.y > 0) || (blacksmith.getPosition().y < 0 && increment.y < 0))
        increment.y = - increment.y;
    */

    sf::Vector2f direction(0.f, 0.f);

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

    //float secondElapsed = .asSeconds();

    sBlacksmith.move(direction.x, direction.y);

}

/********
 * Draw *
 ********/
void State_Dungeon::draw(){

    stateMgr->getContext()->wind->getWindow()->draw(sBlacksmith);
}

/*********
 * Pause *
 *********/
void State_Dungeon::pause(EventDetails *details){

    stateMgr->switchTo(StateType::GamePause);
}