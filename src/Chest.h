#ifndef GAME_CHEST_H
#define GAME_CHEST_H

#include <SFML/Graphics/Sprite.hpp>

#include "Entity.h"

class Chest: public Entity{

public:

    enum State{

        Open,
        Closed
    };

public:

    Chest(TextureManager*, State stat = State::Closed);
    ~Chest();

public:

private:

    void draw(sf::RenderTarget&, sf::RenderStates) const override;

    void toggleState();

private:

    sf::Sprite sprite;

    State state;
};

#endif