#ifndef GAME_MONSTER_H
#define GAME_MONSTER_H

#include "../Character.h"

class Monster : public Character{

public:

    Monster() = delete;
    Monster(const std::string &name, Character*, TextureManager*);
    virtual ~Monster();

public:
    
    virtual void update(sf::Time) = 0;

private:

    void selectTexture();

    void draw(sf::RenderTarget&, sf::RenderStates) const override;
    
protected:
    
    Character* target;

private:
    
    sf::Sprite sprite;
};

#endif
