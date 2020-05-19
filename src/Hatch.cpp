#include "Hatch.h"

/***************
 * Constructor *
 ***************/
Hatch::Hatch(TextureManager *txtMng, sf::Color color):
        Entity(txtMng, Type::Hatch),
        isOpen(true),
        color(color){

    selectHatch();
}

Hatch::~Hatch(){

    textureMgr->releaseResource(textureName);
}

void Hatch::openHatch(){

    isOpen = true;
    textureMgr->releaseResource(textureName);
    selectHatch();
}

bool Hatch::getIsOpen() const{

    return isOpen;
}

void Hatch::selectHatch(){

    if(isOpen){

        textureName = "HatchOpen";

        textureMgr->requireResource(textureName);
        sprite.setTexture(*textureMgr->getResource(textureName));
        
        // TODO find a way to colorize just the bottom part (use 2 sprites ?)

        sf::FloatRect spriteBox = sprite.getLocalBounds();
        collisionBox.left = spriteBox.left;
        collisionBox.top = spriteBox.top + spriteBox.height/2.f;
        collisionBox.width = spriteBox.width;
        collisionBox.height = spriteBox.height/2.f;

        setPosition(610.f, 300.f);
    }
    else{

        textureName = "HatchClosed";

        textureMgr->requireResource(textureName);
        sprite.setTexture(*textureMgr->getResource(textureName));
        
        collisionBox.width = 0.f;
        collisionBox.height = 0.f;

        setPosition(610.f, 330.f);
    }
}

void Hatch::draw(sf::RenderTarget& target, sf::RenderStates states) const{

    states.transform *= getTransform();
    target.draw(sprite, states);
}
