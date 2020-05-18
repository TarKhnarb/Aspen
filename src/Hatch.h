#ifndef GAME_HATCH_H
#define GAME_HATCH_H

#include <SFML/Graphics/Sprite.hpp>

#include <string>

#include "Entity.h"

class Hatch: public Entity{

public:

    Hatch(TextureManager*); // TODO while monsters used in Room, set hatch closed with no collisionBox
    ~Hatch();

public:

    void openHatch();

    bool getIsOpen() const;

private:

    void selectHatch();

    void draw(sf::RenderTarget&, sf::RenderStates) const override;

private:

    bool isOpen;

    sf::Sprite sprite;
    std::string textureName;
};

#endif