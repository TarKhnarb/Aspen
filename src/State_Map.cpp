#include "State_Map.h"
#include "StateManager.h"

/***************
 * Constructor *
 ***************/
State_Map::State_Map(StateManager *stateMgr):
        BaseState(stateMgr),
        map(stateMgr->getContext()->textureManager),
        player(stateMgr->getContext()->textureManager, stateMgr->getContext()->eventManager){

    player.scale(0.5f, 0.5f);
    player.setBaseSpeed(75.f);
    
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
void State_Map::activate(){}

/**************
 * Deactivate *
 **************/
void State_Map::deactivate(){}

/**********
 * Update *
 **********/

void State_Map::update(const sf::Time &time){

    player.update(time);
    map.checkMapCollisions(player);
    setViewOnPlayer();
}

/********
 * Draw *
 ********/
void State_Map::draw(){

    Window* window = stateMgr->getContext()->wind;

    window->getWindow()->setView(getView());
    
    window->draw(map);
    window->draw(player);
}

void State_Map::spawnPointPlayer(){

    player.setPosition(map.getSpawnPoint());
}

void State_Map::setViewOnPlayer(){

    getView().setCenter(player.getPosition().x + 15/2.f, player.getPosition().y + 15.f);
}
