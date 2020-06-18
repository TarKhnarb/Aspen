#include "House.h"

/***************
 * Constructor *
 ***************/
House::House(std::string textureName, TextureManager *txtMgr):
        Entity(txtMgr, Type::House),
        textureName(textureName){

    setSprite();
}

/**************
 * Destructor *
 **************/
House::~House(){

    textureMgr->releaseResource(textureName);
}

/*************
 * SetSprite *
 *************/
void House::setSprite(){

    textureMgr->requireResource(textureName);
    sprite.setTexture(*textureMgr->getResource(textureName));
    collisionBox = sprite.getLocalBounds();

    if(textureName == "BaseHouse" || textureName == "CrafterHouse" || textureName == "TraderHouse")
        scale(71.f / 219.f, 62.f / 186.f);
    else if(textureName == "BlacksmithHouse" || textureName == "WitchHouse")
        scale(53.f / 162.f, 81.f / 252.f);
    else
        scale(228.f/705.f, 196.f/607.f);
    collisionBox.height -= 20.f;
    collisionBox.top += 20.f;
}

/********
 * Draw *
 ********/
void House::draw(sf::RenderTarget &target, sf::RenderStates states) const{

    states.transform *= getTransform();
    target.draw(sprite, states);
}