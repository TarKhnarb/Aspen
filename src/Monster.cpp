#include "Monster.h"

/***************
 * Constructor *
 ***************/
Monster::Monster(std::string name, TextureManager * txtMgr):
        Character(name, txtMgr),
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


}