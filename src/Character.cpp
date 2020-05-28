#include "Character.h"

/***************
 * Constructor *
 ***************/
Character::Character(const std::string &name, Type type, TextureManager *textureMgr):
        Entity(textureMgr, type),
        velocity(0.f, 0.f),
        stats("Data/Files/Characters/" + name + ".cfg"),
        name(name){}

/**************
 * Destructor *
 **************/
Character::~Character(){}

void Character::hit(float damages){
    
    stats.modify(Life, -damages);
}

bool Character::isAlive() const{
    
    return (stats.getFinalValue(Life) > 0.f);
}

/***********
 * GetName *
 ***********/
std::string Character::getName() const{
    
    return name;
}

/***************
 * GetVelocity *
 ***************/
sf::Vector2f Character::getVelocity() const{
    
    return velocity;
}

/************
 * GetStats *
 ************/
Statistics* Character::getStats(){
    
    return &stats;
}
