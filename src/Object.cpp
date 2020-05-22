#include "Object.h"

Object::Object(const std::string &name, TextureManager *txtMgr):
        Entity(txtMgr, Entity::Object),
        name(name){
    
    setSprite(); 
}

Object::~Object(){
    
    textureMgr->releaseResource(name);
}

void Object::setSprite(){
    
    textureMgr->requireResource(name);
    sprite.setTexture(*textureMgr->getResource(name));
    
    collisionBox = sprite.getGlobalBounds();
}

std::string Object::getName() const{
    
    return name;
}

void Object::draw(sf::RenderTarget &target, sf::RenderStates states) const{
    
    states.transform *= getTransform();
    target.draw(sprite, states);
}
