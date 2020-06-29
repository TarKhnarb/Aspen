#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <SFML/Graphics/Sprite.hpp>

#include <string>
#include <cmath>
#include <utility>

#include "../Entity.h"
#include "Bonus.h"

class Object : public Entity{
    
public:
    
    enum ObjectType{

        Stuff,
        Potion,
        Loot,
        Count
    };
    
public:
    
    Object() = delete;
    Object(const std::string&, TextureManager*, std::size_t number = 1);
    Object(const Object *obj, std::size_t number = 1);
    ~Object();
    
public:

    std::string getName() const;
    std::size_t getNumber() const;
    ObjectType getObjectType() const;
    std::size_t getStackSize() const;
    Bonus* getBonus() const;
    std::pair<int, int> getPrices() const;

    bool empty() const;
    bool full() const;

    Object& operator+=(std::size_t&);
    Object& operator+=(Object&);
    Object& operator-=(std::size_t&);
    Object& operator-=(Object&);
    Object& operator++();
    Object& operator--();
    
private:

    virtual void setSprite();

    int usePotion(std::size_t);

    virtual void loadFromFile();

    virtual void draw(sf::RenderTarget&, sf::RenderStates) const;

private:
    
    sf::Sprite sprite;
    
protected:
    
    std::string name;

    std::size_t number;

    ObjectType type;

    std::size_t stackSize;

    Bonus *bonus;

    std::pair<int, int> prices; // 0: buy, 1: sell
};

#endif
