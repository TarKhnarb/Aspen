#ifndef HOLE_H
#define HOLE_H

#include <string>
#include <SFML/Graphics/Sprite.hpp>

#include "Entity.h"

class Hole : public Entity{
    
public:
    
    Hole(bool border, TextureManager*);
    ~Hole();

private:
    
    void draw(sf::RenderTarget&, sf::RenderStates) const override;
    
private:
    
    sf::Sprite sprite;
    std::string textureName;
};
    
#endif
