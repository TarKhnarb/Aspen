#include "Entity.h"

Entity::Entity(TextureManager* textureMgr):
        textureMgr(textureMgr){}

void Entity::setPosition(float x, float y){
    
    sf::Vector2f initialPos = getPosition();
    sf::Transformable::setPosition(x, y);
    sf::Vector2f finalPos = getPosition();
    
    sf::Vector2f offset = finalPos - initialPos;
    collisionBox.left += offset.x;
    collisionBox.top += offset.y;
}

void Entity::setPosition(const sf::Vector2f& position){
    
    sf::Vector2f initialPos = getPosition();
    sf::Transformable::setPosition(position);
    sf::Vector2f finalPos = getPosition();
    
    sf::Vector2f offset = finalPos - initialPos;
    collisionBox.left += offset.x;
    collisionBox.top += offset.y;
}

void Entity::move(float offsetX, float offsetY){
    
    sf::Transformable::move(offsetX, offsetY);
    
    collisionBox.left += offsetX;
    collisionBox.top += offsetY;
}

void Entity::move(const sf::Vector2f& offset){
    
    sf::Transformable::move(offset);
    
    collisionBox.left += offset.x;
    collisionBox.top += offset.y;
}

void Entity::setOrigin(float x, float y){
    
    sf::Transformable::setOrigin(x, y);
    
    // TODO
}

void Entity::setOrigin(const sf::Vector2f &origin){
    
    sf::Transformable::setOrigin(origin);
    
    // TODO
}

Entity::Type Entity::getType() const{
    
    return type;
}
