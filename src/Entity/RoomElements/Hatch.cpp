#include "Hatch.h"

/***************
 * Constructor *
 ***************/
Hatch::Hatch(TextureManager *txtMng, sf::Color color):
        Entity(txtMng, Type::Hatch),
        open(true),
        color(color){

    selectHatch();
}

/**************
 * Destructor *
 **************/
Hatch::~Hatch(){

    textureMgr->releaseResource(textureName);
}

/*************
 * OpenHatch *
 *************/
void Hatch::openHatch(){

    open = true;
    textureMgr->releaseResource(textureName);
    selectHatch();
}

/**********
 * IsOpen *
 **********/
bool Hatch::isOpen() const{

    return open;
}

/***************
 * SelectHatch *
 ***************/
void Hatch::selectHatch(){

    if(open){

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

/********
 * Draw *
 ********/
void Hatch::draw(sf::RenderTarget& target, sf::RenderStates states) const{

    states.transform *= getTransform();
    target.draw(sprite, states);
}
