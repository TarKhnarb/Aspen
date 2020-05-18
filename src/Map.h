#ifndef GAME_MAP_H
#define GAME_MAP_H

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "TextureManager.h"

class Map: public sf::Drawable{

public:

    Map(TextureManager*);
    ~Map();

public:

    //std::pair<Entity::Type, Orientation> checkMapCollisions(Entity&); // TODO when we have added entities

private:

    void setWall(); // TODO place walls to block player front of the sea

    void setNpc(); // TODO place different Npc with their house

    void setBase(); // TODO place the house of Aspen to access at his Base

    int returnStoi(std::istringstream ss);

    void draw(sf::RenderTarget&, sf::RenderStates) const override;

private:

    sf::RectangleShape background;
    sf::Sprite map;


};

#endif