#include "State_Map.h"
#include "StateManager.h"

/***************
 * Constructor *
 ***************/
State_Map::State_Map(StateManager *stateMgr):
        BaseState(stateMgr),
        map(stateMgr->getContext()->textureManager),
        Aspen(*stateMgr->getContext()->aspen){
    
    spawnPointPlayer();
}

/**************
 * Destructor *
 **************/
State_Map::~State_Map(){}

/************
 * OnCreate *
 ************/
void State_Map::onCreate(){

    sf::Vector2f size(640.f, 360.f);

    getView().setSize(size);
    setViewOnPlayer();
}

/*************
 * OnDestroy *
 *************/
void State_Map::onDestroy(){}

/************
 * Activate *
 ************/
void State_Map::activate(){
    
    Aspen.setScale(0.5f, 0.5f);
    Aspen.setBaseSpeed(75.f);
}

/**************
 * Deactivate *
 **************/
void State_Map::deactivate(){}

/**********
 * Update *
 **********/
void State_Map::update(const sf::Time &time){


    Aspen.update(time);
    map.checkMapCollisions(Aspen);
    if(map.checkMapCollisions(Aspen) == Entity::Wall){

        stateMgr->switchTo(StateType::Dungeon);
        stateMgr->remove(StateType::Map);
    }
    setViewOnPlayer();

}

/********
 * Draw *
 ********/
void State_Map::draw(){

    Window* window = stateMgr->getContext()->wind;

    window->getWindow()->setView(getView());
    
    window->draw(map);
    window->draw(Aspen);
}

void State_Map::spawnPointPlayer(){

    Aspen.setPosition(map.getSpawnPoint());
}

void State_Map::setViewOnPlayer(){

    getView().setCenter(Aspen.getPosition().x + 15/2.f, Aspen.getPosition().y + 15.f);
}
