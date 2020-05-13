#include "Hole.h"

Hole::Hole(bool border, TextureManager* textureMgr):
        Entity(textureMgr, Type::Hole){
    
    textureName = border ? "BorderHole" : "Hole";
    
    textureMgr->requireResource(textureName);
    sprite.setTexture(*textureMgr->getResource(textureName));
    
    collisionBox = sprite.getLocalBounds();
}

Hole::~Hole(){
    
    textureMgr->releaseResource(textureName);
}

void Hole::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    
    states.transform *= getTransform();
    target.draw(sprite, states);
}
