#ifndef GAME_ROCK_H
#define GAME_ROCK_H

#include <cstdlib>
#include <string>
#include <SFML/Graphics/Sprite.hpp>

#include "Entity.h"

class Rock : public Entity{

public:

    Rock() = delete;
    Rock(unsigned life, TextureManager*);
    ~Rock();

public: // Functions

    void hit(unsigned damage);

    bool getState() const;

    unsigned getForm() const;

private: // Functions

    void selectForm();
    
    void draw(sf::RenderTarget&, sf::RenderStates) const override;

private: // Variables

    unsigned life;
    unsigned form;
    
    sf::Sprite sprite;
    std::string textureName;
};

#endif
