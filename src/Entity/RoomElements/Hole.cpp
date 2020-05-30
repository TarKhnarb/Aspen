#include "Hole.h"

/***************
 * Constructor *
 ***************/
Hole::Hole(bool border, TextureManager *textureMgr, sf::Color color):
        Entity(textureMgr, Type::Hole),
        color(color){
    
    textureName = border ? "BorderHole" : "Hole";
    
    textureMgr->requireResource(textureName);
    sprite.setTexture(*textureMgr->getResource(textureName));
    sprite.setColor(color);
    
    collisionBox = sprite.getLocalBounds();
}

/**************
 * Destructor *
 **************/
Hole::~Hole(){
    
    textureMgr->releaseResource(textureName);
}

/********
 * Draw *
 ********/
void Hole::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    
    states.transform *= getTransform();
    target.draw(sprite, states);
}
