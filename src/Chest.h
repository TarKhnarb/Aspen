#ifndef GAME_CHEST_H
#define GAME_CHEST_H

#include <SFML/Graphics/Sprite.hpp>
#include <string>

#include "Entity.h"

class Chest: public Entity{

public:

    enum State{

        Open,
        Closed
    };

public:
    
    Chest() = delete;
    Chest(TextureManager*, State = State::Closed);
    ~Chest();

public:
    
    //TODO after inventories
    
private:

    void draw(sf::RenderTarget&, sf::RenderStates) const override;

    void toggleState();
    
    State getState() const;

private:

    sf::Sprite sprite;
    
    std::string textureName;

    State state;
};

#endif
