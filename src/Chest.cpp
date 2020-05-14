#include "Chest.h"

/***************
 * Constructor *
 ***************/
Chest::Chest(TextureManager *textureMgr, State stat):
        state(stat),
        Entity(textureMgr, Type::Chest){

    textureMgr->requireResource("Chest");
    sprite.setTexture(*textureMgr->getResource("Chest"));
    sf::FloatRect rect = sprite.getLocalBounds();
    sprite.setOrigin(rect.width/2.f, rect.height/2.f);
    collisionBox = rect;
}

/***************
 * Constructor *
 ***************/
Chest::~Chest(){

    textureMgr->releaseResource("Chest");
}

/********
 * Draw *
 ********/
void Chest::draw(sf::RenderTarget &target, sf::RenderStates states) const{

    states.transform *= getTransform();
    target.draw(sprite, states);
}