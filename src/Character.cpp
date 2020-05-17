#include "Character.h"

/***************
 * Constructor *
 ***************/
Character::Character(const std::string& name, Type type, TextureManager* textureMgr):
        Entity(textureMgr, type),
        velocity(0.f, 0.f),
        name(name),
        entityState(EntityState::Idle){}

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

/******************
 * GetEntityState *
 ******************/
EntityState Character::getEntityState() const{

    return entityState;
}

/******************
 * SetEntityState *
 ******************/
void Character::setEntityState(EntityState state){

    entityState = state;
}
