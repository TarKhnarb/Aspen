#ifndef GAME_DOOR_H
#define GAME_DOOR_H

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Color.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "../Orientation.h"
#include "../Entity/Entity.h"

class Door: public Entity{

public:

    enum State{

        Open,
        Closed,
        Key
    };

public:

    Door(Orientation orient, State dState, TextureManager*, sf::Color = sf::Color::White);

    ~Door();

public:

    Door::State getState() const;

    void setState(State state);

    Orientation getOrientation() const;

private:

    void placeDoor();

    unsigned returnStoi(std::istringstream &ss);
    
    void draw(sf::RenderTarget&, sf::RenderStates) const override;

private:

    Orientation orientation;
    State state;

    sf::Sprite spriteFrame;
    sf::Sprite spriteDoor;
    std::string textureName;
};

#endif
