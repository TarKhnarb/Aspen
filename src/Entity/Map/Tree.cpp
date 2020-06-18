#include "Tree.h"

/***************
 * Constructor *
 ***************/
Tree::Tree(unsigned value, TextureManager *txtMng):
        Entity(txtMng, Type::Tree){

    setSprite(value);
}

/**************
 * Destructor *
 **************/
Tree::~Tree(){

    textureMgr->releaseResource(textureName);
}

/*************
 * SetSprite *
 *************/
void Tree::setSprite(int number){

    textureName = number%5 == 0 ? "Tree2" : "Tree1";

    textureMgr->requireResource(textureName);
    sprite.setTexture(*textureMgr->getResource(textureName));

    collisionBox = sprite.getLocalBounds();
    scale(38.f/116.f, 46.f/141.f);
    collisionBox.height *= 2.f/3.f;
    collisionBox.top += collisionBox.height/2.f;
}

/********
 * Draw *
 ********/
void Tree::draw(sf::RenderTarget &target, sf::RenderStates states) const{

    states.transform *= getTransform();
    target.draw(sprite, states);
}