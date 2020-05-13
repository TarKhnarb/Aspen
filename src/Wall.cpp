#include "Wall.h"



/***************
 * Constructor *
 ***************/
Wall::Wall():
        Entity(nullptr, Type::Wall),
        left(collisionBox.left),
        top(collisionBox.top),
        width(collisionBox.width),
        height(collisionBox.height){}

/********
 * Draw *
 ********/
void Wall::draw(sf::RenderTarget& target, sf::RenderStates states) const{}
