#include "Entity.h"

Entity::Entity(TextureManager* textureMgr, Type type):
        textureMgr(textureMgr),
        type(type){}

bool Entity::collides(Entity& other, float push){
    
    push = std::max(0.f, std::min(1.f, push)); // must be in [0, 1]
    
    sf::Vector2f thisCenter;
    sf::Vector2f otherCenter;
    
    sf::Vector2f thisRadius;
    sf::Vector2f otherRadius;
    
    thisCenter.x = collisionBox.left + collisionBox.width / 2.f;
    thisCenter.y = collisionBox.top + collisionBox.height / 2.f;
    
    otherCenter.x = other.collisionBox.left + other.collisionBox.width / 2.f;
    otherCenter.y = other.collisionBox.top + other.collisionBox.height / 2.f;
    
    thisRadius.x = collisionBox.width / 2.f;
    thisRadius.y = collisionBox.height / 2.f;
    
    otherRadius.x = other.collisionBox.width / 2.f;
    otherRadius.y = other.collisionBox.height / 2.f;
    
    sf::Vector2f delta = otherCenter - thisCenter;
    sf::Vector2f intersect;
    intersect.x = abs(delta.x) - (thisRadius.x + otherRadius.x);
    intersect.y = abs(delta.y) - (thisRadius.y + otherRadius.y);
    
    if(intersect.x <= 0.f && intersect.y <= 0.f){
        
        if(intersect.x > intersect.y){ // we move along the x-axis
            
            if(delta.x > 0.f){ // this is over other
                move(intersect.x * (1 - push), 0.f);
                other.move(-intersect.x * push, 0.f);
            }
            else{ // this is under other
                move(-intersect.x * (1 - push), 0.f);
                other.move(intersect.x * push, 0.f);
            }
        }
        else{ // along y-axis
            
            if(delta.y > 0.f){ // this is on the left side of other
                move(0.f, intersect.y * (1 - push));
                other.move(0.f, -intersect.y * push);
            }
            else{ // this is on the right side of other
                move(0.f, -intersect.y * (1 - push));
                other.move(0.f, intersect.y * push);
            }
        }
        
        return true;
    }
    
    return false;
}

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

Entity::Type Entity::getType() const{
    
    return type;
}
