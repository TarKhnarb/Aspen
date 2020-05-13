#include "Wall.h"

Wall::Wall():
        Entity(nullptr, Type::Wall),
        left(collisionBox.left),
        top(collisionBox.top),
        width(collisionBox.width),
        height(collisionBox.height){}

void Wall::draw(sf::RenderTarget& target, sf::RenderStates states) const{}
