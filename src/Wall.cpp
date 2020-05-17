#include "Wall.h"



/***************
 * Constructor *
 ***************/
Wall::Wall(float x, float y, float Dx, float Dy):
        Entity(nullptr, Type::Wall),
        left(x),
        top(y),
        width(Dx),
        height(Dy){}

/********
 * Draw *
 ********/
void Wall::draw(sf::RenderTarget& target, sf::RenderStates states) const{}
