#include "State_Dungeon.h"
#include "../StateManager.h"

/***************
 * Constructor *
 ***************/
State_Dungeon::State_Dungeon(StateManager* stateMgr):
        BaseState(stateMgr),
        dungeon(stateMgr->getContext()),
        Aspen(*stateMgr->getContext()->aspen){

    Aspen.setDungeon(&dungeon);
}

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
    stateMgr->switchTo(StateType::Statistics);
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
    
    Projectile *proj = Aspen.getProjectile();
    if(proj){
        
        dungeon.getCurrentRoom()->addProjectile(proj);
    }

    dungeon.getCurrentRoom()->update(time);
    
    dungeon.getCurrentRoom()->checkMonsterCollisions(Aspen);
    dungeon.getCurrentRoom()->checkProjectileCollisions(Aspen);

    std::pair<Entity::Type, Orientation> info = dungeon.getCurrentRoom()->checkRoomCollisions(Aspen);

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
                stateMgr->remove(StateType::Statistics);
            }
            break;

        default:
            break;
    }
    
    dungeon.getCurrentRoom()->processRequests();
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

/****************
 * CenterPlayer *
 ****************/
void State_Dungeon::centerPlayer(){

    sf::Vector2u windowSize = stateMgr->getContext()->wind->getWindow()->getSize();
    Aspen.setPosition((windowSize.x / 2.f) - 15.f, (windowSize.y / 2.f) - 30.f);
}
