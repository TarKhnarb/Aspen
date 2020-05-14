#include "Character.h"

/***************
 * Constructor *
 ***************/
Character::Character(const std::string& name, Type type, TextureManager* textureMgr):
        Entity(textureMgr, type),
        velocity(0.f, 0.f),
        name(name){}

/**************
 * Destructor *
 **************/
Character::~Character(){}

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
