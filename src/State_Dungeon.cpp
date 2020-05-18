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
    player.setPosition((windowSize.x / 2.f) - 15.f, (windowSize.y / 2.f) - 30.f);
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
    
    auto info = dungeon.getCurrentRoom()->checkRoomCollisions(player);
    
    switch(info.first){
        
        case Entity::Door:
            dungeon.changeRoom(info.second);
            player.changeRoom(info.second);
            break;
        
        case Entity::Chest:
            //stateMgr->switchTo(State::Inventory);
            break;

        case Entity::Hatch:
            std::cout << "Hatch" << std::endl;
            dungeon.nextStage();
            centerPlayer();
            break;
        
        default:
            break;
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

void State_Dungeon::centerPlayer(){

    sf::Vector2u windowSize = stateMgr->getContext()->wind->getWindow()->getSize();
    player.setPosition((windowSize.x / 2.f) - 15.f, (windowSize.y / 2.f) - 30.f);
}