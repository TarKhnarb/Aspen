#ifndef GAME_STUFF_H
#define GAME_STUFF_H

#include "Object.h"
#include "Bonus.h"

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
    
    void loadFromFile(const std::string&);
    
    StuffType getStuffType() const;
    Bonus* getBonus();
    
private:
    
    StuffType stuffType;
    
    Bonus bonus;
};  

#endif
