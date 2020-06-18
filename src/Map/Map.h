#ifndef GAME_MAP_H
#define GAME_MAP_H

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System.hpp>

#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>

#include "../TextureManager.h"
#include "../Entity/RoomElements/Wall.h"
#include "../Entity/Map/House.h"

class Map: public sf::Drawable{

public:

    Map(TextureManager*);
    ~Map();

public:

    Entity::Type checkMapCollisions(Entity&); // TODO when we have added entities

    sf::Vector2f getSpawnPoint() const;

private:

    void placeWalls(); // TODO change to a better algorithm which made the biggest rectangle of walls for a lighten code

    void placeNpcs(); // TODO place different Npc with their house

    void placeTrees(); // TODO place all trees (25)

    void placeHouses(); // TODO place Npc Houses, Base and Dungeon

    int returnStoi(std::istringstream ss);

    void draw(sf::RenderTarget&, sf::RenderStates) const override;

private:

    TextureManager *txtMng;

    sf::RectangleShape background;
    sf::Sprite map;
    std::vector<std::unique_ptr<House>> houses;

    std::vector<std::unique_ptr<Wall>> walls;
    Wall dungeonDoor;

    sf::Vector2f spawnPoint;
};

#endif
