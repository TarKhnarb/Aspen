#include "State_Statistics.h"
#include "StateManager.h"

/***************
 * Constructor *
 ***************/
State_Statistics::State_Statistics(StateManager *stateMgr):
        BaseState(stateMgr),
        Aspen(*stateMgr->getContext()->aspen){}

/**************
 * Destructor *
 **************/
State_Statistics::~State_Statistics(){}

/************
 * OnCreate *
 ************/
void State_Statistics::onCreate(){

    setTransparent(true);
    setTranscendent(true);

    maxLife = sf::RectangleShape({30.f, 100.f});
    maxLife.setPosition({2.f, 2.f});
    maxLife.setFillColor(sf::Color::Transparent);
    maxLife.setOutlineColor(sf::Color::Red);
    maxLife.setOutlineThickness(2.f);

    actualLife = sf::RectangleShape({30.f, 100.f});
    actualLife.setPosition({2.f, 2.f});
    actualLife.setFillColor(sf::Color::Green);
}

/*************
 * OnDestroy *
 *************/
void State_Statistics::onDestroy(){}

/**********
 * Update *
 **********/
void State_Statistics::update(const sf::Time &time){

    float life = Aspen.getStats()->getFinalValue(Life) / Aspen.getStats()->getFinalValue(MaxLife);
    actualLife.setSize({30.f, 100.f * life});
    actualLife.setPosition(2.f, 2.f + 100.f - actualLife.getSize().y);
}

/********
 * Draw *
 ********/
void State_Statistics::draw(){

    Window* window = stateMgr->getContext()->wind;

    window->draw(maxLife);
    window->draw(actualLife);
}

