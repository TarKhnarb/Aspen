#ifndef GAME_CHARACTER_H
#define GAME_CHARACTER_H

#include <SFML/Graphics/Sprite.hpp>

#include "Entity.h"
#include "CharacterStats.h"

class Character : public Entity{

    friend class
public:

    Character(CharacterType charType, std::string charName, TextureManager*);
    ~Character();

public:

    void update(float deltaT, characterType charType);

private:

    void draw(sf::RenderTarget&, sf::RenderStates) const override;

private:

    CharacterType characterType;
    std::string characterName;

    CharactereStats stats;
};

#endif