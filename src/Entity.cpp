#include "Entity.h"

/***************
 * Constructor *
 ***************/
Entity::Entity(TextureManager* textureMgr, Type type):
        textureMgr(textureMgr),
        type(type){}

/************
 * Collides *
 ************/
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
    intersect.x = fabs(delta.x) - (thisRadius.x + otherRadius.x);
    intersect.y = fabs(delta.y) - (thisRadius.y + otherRadius.y);
    
    if(intersect.x < 0.f && intersect.y < 0.f){
        
        if(intersect.x > intersect.y){ // we move along the x-axis
            
            if(delta.x > 0.f){ // this is on the left side of other
                move(intersect.x * (1 - push), 0.f);
                other.move(-intersect.x * push, 0.f);
            }
            else{ // this is on the right side of other
                move(-intersect.x * (1 - push), 0.f);
                other.move(intersect.x * push, 0.f);
            }
        }
        else{ // along y-axis
            
            if(delta.y > 0.f){ // this is over other
                move(0.f, intersect.y * (1 - push));
                other.move(0.f, -intersect.y * push);
            }
            else{ // this is under other
                move(0.f, -intersect.y * (1 - push));
                other.move(0.f, intersect.y * push);
            }
        }
        
        return true;
    }
    
    return false;
}

/********
 * Move *
 ********/
void Entity::move(float offsetX, float offsetY){
    
    sf::Transformable::move(offsetX, offsetY);
    
    collisionBox.left += offsetX;
    collisionBox.top += offsetY;
}

void Entity::move(const sf::Vector2f& offset){
    
    move(offset.x, offset.y);
}

/***************
 * SetPosition *
 ***************/
void Entity::setPosition(float x, float y){
    
    move(sf::Vector2f(x, y) - getPosition());
}

void Entity::setPosition(const sf::Vector2f& position){
    
    setPosition(position.x, position.y);
}

/*************
 * SetOrigin *
 *************/
void Entity::setOrigin(float x, float y){
    
    sf::Vector2f initialOrigin = getOrigin();
    sf::Transformable::setOrigin(x, y);
    sf::Vector2f finalOrigin = getOrigin();
    
    sf::Vector2f movement = initialOrigin - finalOrigin;
    collisionBox.left += movement.x;
    collisionBox.top += movement.y;
}
 
void Entity::setOrigin(const sf::Vector2f &origin){
    
    setOrigin(origin.x, origin.y);
}

/************
 * SetScale *
 ************/

void Entity::scale(float xZoom, float yZoom){
    
    sf::Vector2f pos = getPosition();
    
    sf::Transformable::scale(xZoom, yZoom);
    
    collisionBox.width *= xZoom;
    collisionBox.height *= yZoom;
    
    collisionBox.left = pos.x + (collisionBox.left - pos.x) * xZoom;
    collisionBox.top = pos.y + (collisionBox.top - pos.y) * yZoom;
}

void Entity::scale(sf::Vector2f zoom){
    
    scale(zoom.x, zoom.y);
}

void Entity::setScale(sf::Vector2f zoom){
    
    scale(zoom - getScale());
}

void Entity::setScale(float xZoom, float yZoom){
    
    setScale(sf::Vector2f(xZoom, yZoom));
}

/***********
 * GetType *
 ***********/
Entity::Type Entity::getType() const{
    
    return type;
}

/***********
 * setType *
 ***********/
void Entity::setType(Type newType){
    
    type = newType;
}
