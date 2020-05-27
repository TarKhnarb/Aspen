#ifndef GAME_MONSTER_H
#define GAME_MONSTER_H

class Monster: public Character{

public:

    Monster() = delete;
    Monster(std::string name, TextureManager*);
    virtual ~Monster();

public:

    virtual void update(sf::Time time) = 0;

private:

    void selectTexture();

    virtual void draw(sf::RenderTarget&, sf::RenderStates) const = 0;

private:

    std::string name;
    sf::Sprite sprite;

};

#endif