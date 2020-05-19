#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <string>
#include <SFML/Graphics/Sprite.hpp>

#include "Entity.h"

class Object : public Entity{
    
public:
    
    Object() = delete;
    Object(const std::string&, TextureManager*);
    
public:
    
    void loadFromFile(const std::string&);
    
    std::string getName() const;
    int getBuyPrice() const;
    int getSellPrice() const;
    
protected:
    
    void draw(sf::RenderTarget&, sf::RenderStates) const override;
    
private:
    
    sf::Sprite sprite;
    
protected:
    
    std::string name;
    
    int buyPrice;
    int sellPrice;
};

#endif
