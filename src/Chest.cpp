#include "Chest.h"

/***************
 * Constructor *
 ***************/
Chest::Chest(TextureManager *textureMgr, State state):
        Entity(textureMgr, Type::Chest),
        state(state){

    textureName = (state == State::Closed) ? "ClosedChest" : "OpenChest";
    textureMgr->requireResource(textureName);
    sprite.setTexture(*textureMgr->getResource(textureName));

    sf::FloatRect rect = sprite.getLocalBounds();

    collisionBox = rect;
}

/***************
 * Constructor *
 ***************/
Chest::~Chest(){

    textureMgr->releaseResource(textureName);
}

/********
 * Draw *
 ********/
void Chest::draw(sf::RenderTarget &target, sf::RenderStates states) const{

    states.transform *= getTransform();
    target.draw(sprite, states);
}

/***************
 * ToggleState *
 ***************/
void Chest::toggleState(){

    state = (state == State::Closed) ? State::Open : State::Closed;

    textureMgr->releaseResource(textureName);
    textureName = (state == State::Closed) ? "ClosedChest" : "OpenChest";
    textureMgr->requireResource(textureName);

    sprite.setTexture(*textureMgr->getResource(textureName));
}

/************
 * GetState *
 ************/
Chest::State Chest::getState() const{
    
    return state;
}
