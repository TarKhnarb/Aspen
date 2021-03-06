#ifndef GAME_INVENTORY_H
#define GAME_INVENTORY_H

#include <vector>
#include <memory>

#include "Object/Stuff.h"

class Inventory{
    
public:

    Inventory() = delete;
    Inventory(bool, std::size_t);

public:

    bool addObject(Object&);
    bool removeObject(Object&);
    bool removeObject(const std::string&, std::size_t nb = 1); // Pasage en données résultat pas nécésssaire pour le nb (A voir)
    bool removeObject(std::size_t, std::size_t nb = 1);
    void clearObject(std::size_t);
    std::size_t numberOf(const std::string&) const;
    
    Bonus* equip(std::size_t);
    Bonus* unequip(std::size_t);

    void refillStacks();
    void sort();

    unsigned getBagSize() const;
    unsigned getStuffSize() const;
    
    Stuff* getStuff(std::size_t);
    Object* getObject(std::size_t);
    
private:
    
    std::vector<std::unique_ptr<Stuff>> stuff;
    std::vector<std::unique_ptr<Object>> bag;

    bool hasStuff;
};

Object* newObject(const Object&);

#endif
