#include "Monster.h"

/***************
 * Constructor *
 ***************/
Monster::Monster(std::string name, TextureManager * txtMgr):
        Character(name, Type::Monster, txtMgr),
        name(name){

    selectTexture();
}

/**************
 * Destructor *
 **************/
Monster::~Monster(){}


/*****************
 * SelectTexture *
 *****************/
void Monster::selectTexture(){

    textureMgr->requireResource(name);
    sprite.setTexture(*textureMgr->getResource(textureName));

    collisionBox = sprite.getLocalBounds();
}
