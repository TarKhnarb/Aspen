#include "Rock.h"

/***************
 * Constructor *
 ***************/
Rock::Rock(unsigned life, TextureManager* textureMgr):
        Entity(textureMgr),
        life (life){

    type = Type::Rock;
    selectForm();
}

Rock::~Rock(){
    
    if(textureMgr){
        textureMgr->releaseResource(textureName);
    }
}

/*******
 * Hit *
 *******/
void Rock::hit(unsigned damage){

    if(life > damage)
        life -= damage;
    else{
        life = 0;
        
        textureMgr->requireResource("BrokenRock");
        sprite.setTexture(*textureMgr->getResource("BrokenRock"));
        textureMgr->releaseResource(textureName);
        textureName = "BrokenRock";
    }
}

/************
 * GetState *
 ************/
bool Rock::getState() const{

    return life != 0;
}

/***********
 * GetForm *
 ***********/
unsigned Rock::getForm() const{

    return form;
}

/**************
 * SelectForm *
 **************/
void Rock::selectForm(){

    form = rand()%3;
    
    textureName = "Rock" + std::to_string(form + 1);
    
    textureMgr->requireResource(textureName);
    sprite.setTexture(*textureMgr->getResource(textureName));
}

/********
 * draw *
 ********/

void Rock::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    
    states.transform *= getTransform();
    target.draw(sprite, states);
}
