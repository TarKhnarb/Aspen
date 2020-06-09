#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <string>
#include <cmath>
#include <SFML/Graphics/Sprite.hpp>

#include "../Entity.h"

class Object : public Entity{
    
public:
    
    enum ObjectType{
        
        Weapon,
        Helmet,
        Amulet,
        ChestPlate,
        Leggings,
        Boots,
        StuffCount,
        
        Potion,
        Loot
    };
    
public:
    
    Object() = delete;
    Object(const std::string&, TextureManager*, std::size_t = 1);
    ~Object();
    
public:
    
    std::string getName() const;
    int getBuyPrice() const;
    int getSellPrice() const;
    
    std::size_t getNumber() const;
    std::size_t getStackSize() const;
    bool empty() const;
    
    Object& operator+=(std::size_t&);
    Object& operator+=(Object&);
    Object& operator-=(std::size_t&);
    Object& operator-=(Object&);
    Object& operator++();
    Object& operator--();
    
    virtual int use(std::size_t = 1);
    virtual ObjectType getObjectType() const;
    virtual Bonus* getBonus();
    
private:
    
    virtual void loadFromFile();
    
    void setSprite();
    
    void draw(sf::RenderTarget&, sf::RenderStates) const override;
    
private:
    
    sf::Sprite sprite;
    
    std::size_t number;
    
protected:
    
    std::size_t stackSize;
    
    std::string name;
    
    int buyPrice;
    int sellPrice;
};

#endif
