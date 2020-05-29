#include "Character.h"

/***************
 * Constructor *
 ***************/
Character::Character(const std::string &name, Type type, TextureManager *textureMgr):
        Entity(textureMgr, type),
        velocity(0.f, 0.f),
        stats("Data/Files/Characters/" + name + ".cfg"),
        name(name),
        baseSpeed(0.f){}

/**************
 * Destructor *
 **************/
Character::~Character(){}

void Character::hit(float damages){
    
    stats.modify(Life, -damages);
}

void Character::setBaseSpeed(float newSpeed){
    
    if(newSpeed >= 0.f){
        
        baseSpeed = newSpeed;
    }
}

float Character::getBaseSpeed() const{
    
    return baseSpeed;
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
