#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

#include "TextureManager.h"

class Entity : public sf::Drawable, public sf::Transformable{

public:
    
    enum Type{
        
        Rock
    };
    
public:
    
    Entity(TextureManager*);
    virtual ~Entity() {}
    
    // bool collides(Entity&, float);
    
    void setPosition(float x, float y);
    void setPosition(const sf::Vector2f& position);
    void move(float offsetX, float offsetY);
    void move(const sf::Vector2f& offset);
    void setOrigin(float x, float y);
    void setOrigin(const sf::Vector2f &origin);
    
    Type getType() const;
    
private:
    
    virtual void draw(sf::RenderTarget&, sf::RenderStates) const = 0;
    
protected:
    
    sf::FloatRect collisionBox;
    
    TextureManager* textureMgr;
    
    Type type;
};

#endif // ENTITY
