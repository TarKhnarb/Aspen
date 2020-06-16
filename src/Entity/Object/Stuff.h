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
    Stuff(Object*);

    ~Stuff();
    
public:

    StuffType getStuffType() const;

private:

    void loadFromFile();

private:
    
    StuffType stuffType;
    Object *object;
};  

#endif
