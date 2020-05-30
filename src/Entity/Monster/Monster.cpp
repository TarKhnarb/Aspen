#include "Monster.h"

/***************
 * Constructor *
 ***************/
Monster::Monster(const std::string &name, Character *target, TextureManager *txtMgr):
        Character(name, Type::Monster, txtMgr),
        target(target){
    
    setBaseSpeed(150.f);
    
    selectTexture();
}

/**************
 * Destructor *
 **************/
Monster::~Monster(){
    
    textureMgr->releaseResource(getName());
}

/*****************
 * SelectTexture *
 *****************/
void Monster::selectTexture(){

    textureMgr->requireResource(getName());
    sprite.setTexture(*textureMgr->getResource(getName()));

    collisionBox = sprite.getLocalBounds();
}

void Monster::draw(sf::RenderTarget &target, sf::RenderStates states) const{
    
    states.transform *= getTransform();
    target.draw(sprite, states);
}
