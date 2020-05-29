#ifndef GAME_PROJECTILE_H
#define GAME_PROJECTILE_H

#include <SFML/Graphics/Sprite.hpp>

#include "Entity.h"
#include "Orientation.h"

class Character;

class Projectile : public Entity{

public:

    Projectile() = delete;
    Projectile(Character *owner, Orientation orient, TextureManager*);
    ~Projectile();

public:

    Character* getOwner();
    
    void update(sf::Time);

private:

    void setVelocity();

    void selectProjectile();

    void draw(sf::RenderTarget&, sf::RenderStates) const override;

private:

    Character *owner;

    Orientation orientation;

    float speed;

    sf::Vector2f velocity;

    std::string textureName;
    sf::Sprite spriteProj;
};

#endif
