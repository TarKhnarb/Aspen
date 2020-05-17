#include "State_Dungeon.h"
#include "StateManager.h"

/***************
 * Constructor *
 ***************/
State_Dungeon::State_Dungeon(StateManager* stateMgr):
        BaseState(stateMgr),
        dungeon(stateMgr->getContext()->textureManager),
        player(stateMgr->getContext()->textureManager, stateMgr->getContext()->eventManager){}

/**************
 * Destructor *
 **************/
State_Dungeon::~State_Dungeon(){}

/************
 * OnCreate *
 ************/
void State_Dungeon::onCreate(){
    
    sf::Vector2u windowSize = stateMgr->getContext()->wind->getWindow()->getSize();
    player.setPosition(windowSize.x / 2.f, windowSize.y / 2.f);
}

/*************
 * OnDestroy *
 *************/
void State_Dungeon::onDestroy(){}

/************
 * Activate *
 ************/
void State_Dungeon::activate(){}

/**************
 * Deactivate *
 **************/
void State_Dungeon::deactivate(){}

/**********
 * Update *
 **********/
void State_Dungeon::update(const sf::Time &time){
    
    player.update(time);
    
    dungeon.getCurrentRoom()->checkRoomCollisions(player);
    
    
    // TEMPORARY
    sf::Vector2u windowSize = stateMgr->getContext()->wind->getWindow()->getSize();
    
    if(player.getPosition().x < 0){

        player.setPosition(windowSize.x / 2.f, windowSize.y / 2.f);
        dungeon.changeRoom(Orientation::North);
    }
    if(player.getPosition().y < 0){

        player.setPosition(windowSize.x / 2.f, windowSize.y / 2.f);
        dungeon.changeRoom(Orientation::West);
    }
    if(player.getPosition().x + 40.f > windowSize.x){

        player.setPosition(windowSize.x / 2.f, windowSize.y / 2.f);
        dungeon.changeRoom(Orientation::South);
    }
    if(player.getPosition().y + 80.f > windowSize.y){

        player.setPosition(windowSize.x / 2.f, windowSize.y / 2.f);
        dungeon.changeRoom(Orientation::East);
    }
}

/********
 * Draw *
 ********/
void State_Dungeon::draw(){

    Window* window = stateMgr->getContext()->wind;
    
    window->draw(*dungeon.getCurrentRoom());
    window->draw(player);
}

/*********
 * Pause *
 *********/
void State_Dungeon::pause(EventDetails *details){

    stateMgr->switchTo(StateType::GamePause);
}
