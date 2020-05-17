#include "Wall.h"



/****************
 * Constructors *
 ****************/
Wall::Wall():
        Entity(nullptr, Type::Wall),
        left(collisionBox.left),
        top(collisionBox.top),
        width(collisionBox.width),
        height(collisionBox.height){}

Wall::Wall(float x, float y, float Dx, float Dy):
        Entity(nullptr, Type::Wall),
        left(collisionBox.left),
        top(collisionBox.top),
        width(collisionBox.width),
        height(collisionBox.height){
            
            left = x;
            top = y;
            width = Dx;
            height = Dy;
 }

/********
 * Draw *
 ********/
void Wall::draw(sf::RenderTarget& target, sf::RenderStates states) const{}
