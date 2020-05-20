#include "State_Dungeon.h"
#include "StateManager.h"

/***************
 * Constructor *
 ***************/
State_Dungeon::State_Dungeon(StateManager* stateMgr):
        BaseState(stateMgr),
        dungeon(stateMgr->getContext()->textureManager),
        Aspen(*stateMgr->getContext()->aspen){}

/**************
 * Destructor *
 **************/
State_Dungeon::~State_Dungeon(){}

/************
 * OnCreate *
 ************/
void State_Dungeon::onCreate(){
    
    centerPlayer();
}

/*************
 * OnDestroy *
 *************/
void State_Dungeon::onDestroy(){}

/************
 * Activate *
 ************/
void State_Dungeon::activate(){
    
    Aspen.setScale(1.f, 1.f);
    Aspen.setBaseSpeed(150.f);
}

/**************
 * Deactivate *
 **************/
void State_Dungeon::deactivate(){}

/**********
 * Update *
 **********/
void State_Dungeon::update(const sf::Time &time){
    
    Aspen.update(time);
    
    auto info = dungeon.getCurrentRoom()->checkRoomCollisions(Aspen);
    
    switch(info.first){
        
        case Entity::Door:
            dungeon.changeRoom(info.second);
            Aspen.changeRoom(info.second);
            break;
        
        case Entity::Chest:
            //stateMgr->switchTo(State::Inventory);
            break;

        case Entity::Hatch:
            if(!dungeon.end()){

                dungeon.nextStage();
                centerPlayer();
            }
            else{

                stateMgr->switchTo(StateType::GameOver);
                stateMgr->remove(StateType::Dungeon);
            }
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
    window->draw(Aspen);
}

/*********
 * Pause *
 *********/
void State_Dungeon::pause(EventDetails *details){

    stateMgr->switchTo(StateType::GamePause);
}

void State_Dungeon::centerPlayer(){

    sf::Vector2u windowSize = stateMgr->getContext()->wind->getWindow()->getSize();
    Aspen.setPosition((windowSize.x / 2.f) - 15.f, (windowSize.y / 2.f) - 30.f);
}
