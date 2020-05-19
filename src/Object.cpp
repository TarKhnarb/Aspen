#include "Object.h"

Object::Object(const std::string& name, TextureManager* txtMgr):
        Entity(txtMgr, Entity::Object),
        name(name){
    
    loadFromFile(name); 
}

void Object::loadFromFile(const std::string& name){
    
    // TODO convert name into filename
    // TODO read texture bound to the name, and load the texture
}

std::string Object::getName() const{
    
    return name;
}

void Object::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    
    states.transform *= getTransform();
    target.draw(sprite, states);
}
