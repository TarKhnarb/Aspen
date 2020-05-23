#ifndef GAME_CHARACTER_H
#define GAME_CHARACTER_H

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Time.hpp>

#include "Entity.h"

class Character : public Entity{

public:

    Character() = delete;
    Character(const std::string&, Type, TextureManager*);
    virtual ~Character();

public:

    virtual void update(sf::Time) = 0;
    
    std::string getName() const;
    sf::Vector2f getVelocity() const;
    
private:

    virtual void draw(sf::RenderTarget&, sf::RenderStates) const = 0;

protected:
    
    sf::Vector2f velocity;
    
private:

    std::string name;
};

#endif
