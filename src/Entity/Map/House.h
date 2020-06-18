#ifndef GAME_HOUSE_H
#define GAME_HOUSE_h

#include <SFML/Graphics/Sprite.hpp>

#include <string>

#include "../Entity.h"

class House: public Entity{

public:

    House() = delete;
    House(std::string, TextureManager*);

    ~House();

private:

    void setSprite();

    void draw(sf::RenderTarget&, sf::RenderStates) const override;

private:

    sf::Sprite sprite;

    std::string textureName;
};

#endif