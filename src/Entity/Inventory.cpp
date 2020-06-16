#include "Inventory.h"

Inventory::Inventory(bool hasStuff, std::size_t bagSize):
        bag(bagSize, nullptr),
        hasStuff(hasStuff){
            
    if(hasStuff)
        stuff.assign(static_cast<int>(Stuff::StuffCount), nullptr);
}


bool Inventory::addObject(Object &toAdd){
    
    if(!toAdd.getObjectType() != Object::Stuff){ // insinu que c'est soit un loot soit une potion donc "stackable"
        
        for(const auto &object : bag)
            if(object && (object->getName() == toAdd.getName()))
                *object += toAdd;
        
        if(!toAdd.empty()){
            
            for(auto &object : bag){
                
                if(!object){
                    
                    object.reset(new Object(toAdd));
                    toAdd -= toAdd; // clean toAdd
                    return true;
                }
            }
        }
    }
    else{
        
        for(auto &object : bag){
            
            if(!object){
                
                object.reset(new Object(toAdd));
                return true;
            }
        }
    }
    
    return false;
}

bool Inventory::removeObject(Object &toRemove){

    if(toRemove.getObjectType() != Object::Stuff){
        
        for(const auto &object : bag)
            if(object && object->getObjectType() != Object::Stuff)
                *object -= toRemove;
        
        if(!toRemove.empty())
            return false;
        
        return true;
    }
    else{
        
        for(auto &object : bag){
            
            if(object && object->getName() == toRemove.getName()){
            
                object.release();
                return true;
            }
        }
        
        return false;
    }
}

bool Inventory::removeObject(const std::string &toRemove, std::size_t nb){
    
    for(auto &object : bag){
        
        if(object && object->getName() == toRemove){
            
            if(object->getObjectType() != Object::Stuff) {

                Object obj(*object, nb);
                *object -= obj;
            }
            else if(nb >= 1){
                
                object.release();
                --nb;
            }
        }
    }
    
    return (nb == 0);
}

bool Inventory::removeObject(std::size_t index, std::size_t nb){
    
    if(index >= bag.size())
        return false;
    
    if(bag[index]){
        
        if(bag[index]->getObjectType() != Object::Stuff){

            Object obj(*bag[index], nb);
            *bag[index] -= obj;
        }
        else if(nb >= 1){
            
            bag[index].release();
            --nb;
        }
    }
    
    return (nb == 0);
}

void Inventory::clearObject(std::size_t index){
    
    if(index >= bag.size()){
        
        return;
    }
    
    if(bag[index]){
        
        if(bag[index]->getObjectType() != Object::Stuff)
            removeObject(index, bag[index]->getNumber());
        else
            removeObject(index);
    }
}

std::size_t Inventory::numberOf(const std::string &name) const{
    
    std::size_t count = 0;
    
    for(const auto &object : bag){

        if(object && object->getName() == name){

            if(object->getObjectType() != Object::Stuff)
                count += object->getNumber();
            else
                ++count;
        }
    }
    
    return count;
}

Bonus* Inventory::equip(std::size_t index){

    if(hasStuff){

        if (index >= bag.size())
            return nullptr;

        if (bag[index] && bag[index]->getObjectType() == Object::Stuff) {

            Stuff::StuffType type = Stuff(bag[index]->getName(), bag[index]->getTextureManager()).getStuffType();
            if (!stuff[type]) {

                stuff[type] = std::move(bag[index]);
                bag[index].release();
                return stuff[type]->getBonus();
            }
        }
    }
    
    return nullptr;
}
            
Bonus* Inventory::unequip(std::size_t index){ // can be used with Stuff::StuffType index

    if(hasStuff){

        if (index >= stuff.size())
            return nullptr;

        if (stuff[index]) {

            Bonus *bonus = stuff[index]->getBonus();
            if (addObject(*stuff[index])) {

                stuff[index].release();
                return bonus;
            }
        }
    }
    
    return nullptr;
}

void Inventory::refillStacks(){}
void Inventory::sort(){}

/*************
 * Accessors *
 *************/

Stuff* Inventory:: getStuff(std::size_t index){
    
    return stuff[index].get();
}

Object* Inventory::getObject(std::size_t index){
    
    return bag[index].get();
}
