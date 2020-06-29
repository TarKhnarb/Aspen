#include "State_Inventory.h"
#include "../StateManager.h"

/***************
 * Constructor *
 ***************/
State_Inventory::State_Inventory(StateManager *stateMgr):
        BaseState(stateMgr),
        Player(*stateMgr->getContext()->aspen){}

/**************
 * Destructor *
 **************/
State_Inventory::~State_Inventory(){}

/************
 * OnCreate *
 ************/
void State_Statistics::onCreate(){

    setTransparent(true);
    //setTranscendent(true); // TODO A voir si necessaire

    background = RectangleShape({640.f, 360.f});
    background.setFillColor(sf::Color::White);
    background.setPosition({320.f, 180.f});
}

/*************
 * OnDestroy *
 *************/
void State_Inventory::onDestroy(){

    Aspen = nullptr;
}

/**********
 * Update *
 **********/
void State_Inventory::update(){}

/********
 * Draw *
 ********/
void State_Inventory::draw(){

    Window* window = stateMgr->getContext()->wind;

    window->draw(background);

    Inventory *inventory = Aspen->getInventory();
    unsigned cntLine = 0;
    unsigned cntCol = 0
    for(unsigned i = 0; i < inventory->getBagSize(); ++i){

        auto obj = inventory->getObject(i);
        if(cntLine == 7){

            ++cntCol;
            cntLine = 0;
        }
        if(obj){

            obj->setPosition(420.f + cntLine * 64.f, 280.f + cntCol * 64.f);
            window->draw(obj);
        }
        count++;
    }
}