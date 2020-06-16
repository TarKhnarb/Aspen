#ifndef GAME_STUFF_H
#define GAME_STUFF_H

#include "Object.h"

class Stuff : public Object{
    
public:
    
    enum StuffType{
        
        Weapon,
        Helmet,
        Amulet,
        ChestPlate,
        Leggings,
        Boots,
        StuffCount
    };
    
public:
    
    Stuff() = delete;
    Stuff(const std::string&, TextureManager*);
    
public:

    StuffType getStuffType() const;

private:

    void loadFromFile() override;

    void draw(sf::RenderTarget &, sf::RenderStates) const override;

    void setSprite() override;

private:
    
    StuffType stuffType;

    sf::Sprite sprite;
};  

#endif
