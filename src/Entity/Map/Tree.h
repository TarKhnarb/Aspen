#ifndef GAME_TREE_H
#define GAME_TREE_H

#include <SFML/Graphics/Sprite.hpp>

#include "../Entity.h"

class Tree: public Entity{

public:

    Tree() = delete;
    Tree(unsigned value, TextureManager*);

    ~Tree();

private:

    void setSprite(int number);

    void draw(sf::RenderTarget&, sf::RenderStates) const override;

private:

    sf::Sprite sprite;

    std::string textureName;
};

#endif