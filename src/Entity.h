#ifndef GAME_ENTITY_H
#define GAME_ENTITY_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <cstdlib>
#include <cmath>

#include "TextureManager.h"

class Entity: public sf::Drawable, public sf::Transformable{

public:
    
    enum Type{
        
        None,
        Rock,
        Hole,
        Chest,
        Boost,
        Door,
        Hatch,
        Wall,
        Player,
        Monster,
        Object,
        Stuff,
        StackObject,
        Potion,
        Projectile
    };
    
public:
    
    Entity(TextureManager*, Type = None);
    virtual ~Entity() {}
    
public:

    bool collides(Entity&, float);
    
    void move(float offsetX, float offsetY);
    void move(const sf::Vector2f& offset);
    
    void setPosition(float x, float y);
    void setPosition(const sf::Vector2f &position);
    
    void setOrigin(float x, float y);
    void setOrigin(const sf::Vector2f &origin);
    
    void scale(float, float);
    void scale(sf::Vector2f);
    
    void setScale(sf::Vector2f);
    void setScale(float, float);
    
    Type getType() const;
    
protected:
    
    void setType(Type);
    
private:
    
    virtual void draw(sf::RenderTarget&, sf::RenderStates) const = 0;
    
protected:
    
    sf::FloatRect collisionBox;
    
    TextureManager* textureMgr;
    
    Type type;
};

#endif
