#ifndef GAME_HOLE_H
#define GAME_HOLE_H

#include <string>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Color.hpp>

#include "../Entity.h"

class Hole : public Entity{
    
public:
    
    Hole() = delete;
    Hole(bool border, TextureManager*, sf::Color = sf::Color::White);
    ~Hole();

private:
    
    void draw(sf::RenderTarget&, sf::RenderStates) const override;
    
private:
    
    sf::Sprite sprite;
    sf::Color color;
    std::string textureName;
};
    
#endif
