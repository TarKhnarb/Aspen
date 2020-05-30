#include "Inventory.h"

Inventory::Inventory(bool hasStuff, std::size_t bagSize):
        bag(bagSize, nullptr){
            
    if(hasStuff){
        
        stuff.resize(Stuff::StuffCount, nullptr);
    }
}


bool Inventory::addObject(Object &toAdd){
    
    if(toAdd.getType() == Entity::StackObject){
        
        for(const auto &object : bag){
            
            if(object && object->getType() == Entity::StackObject){
                
                *object += toAdd;
            }
        }
        
        if(!toAdd.empty()){
            
            for(auto &object : bag){
                
                if(!object){
                    
                    object.reset(newObject(toAdd));
                    toAdd -= toAdd.getNumber(); // clean toAdd
                    return true;
                }
            }
        }
    }
    else{
        
        for(auto &object : bag){
            
            if(!object){
                
                object.reset(newObject(toAdd));
                return true;
            }
        }
    }
    
    return false;
}

bool Inventory::removeObject(Object &toRemove){
    
    if(toRemove.getType() == Entity::StackObject){
        
        for(const auto &object : bag){
            
            if(object && object->getType() == Entity::StackObject){
                
                *object -= toRemove;
            }
        }
        
        if(!toRemove.empty()){
            
            return false;
        }
        
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

bool Inventory::removeObject(const std::string &toRemove, std::size_t &nb = 1){
    
    for(auto &objet : bag){
        
        if(object && object->getName() == toRemove){
            
            if(object->getType() == Entity::StackObject){
                
                *object -= nb;
            }
            else if(nb >= 1){
                
                object.release();
                --nb;
            }
        }
    }
    
    return (nb == 0);
}

bool Inventory::removeObject(std::size_t index, std::size_t &nb){
    
    if(index >= bag.size()){
        
        return false;
    }
    
    if(bag[index]){
        
        if(bag[index]->getType() == Entity::StackObject){
            
            *bag[index] -= nb;
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
        
        if(bag[index]->getType() == Entity::StackObject){
            
            removeObject(index, bag[index]->getNumber());
        }
        else{
            
            removeObject(index);
        }
    }
}

std::size_t Inventory::numberOf(const std::string &name) const{
    
    std::size_t count = 0;
    
    for(const auto &object : bag){
        
        if(object && object->getName() == name){
            
            if(object->getType() == Entity::StackObject){
                
                count += object->getNumber();
            }
            else{
                
                ++count;
            }
        }
    }
    
    return count;
}

Bonus* Inventory::equip(std::size_t index){
    
    if(index >= bag.size()){
        
        return nullptr;
    }
    
    if(bag[index] && bag[index]->getType() == Entity::Stuff){
        
        Stuff::StuffType type = bag[index]->getStuffType()
        
        if(!stuff[type]){
            
            stuff[type] = std::move(bag[index]);
            bag[index].release();
            return stuff[type]->getBonus();
        }
    }
    
    return nullptr;
}
            
Bonus* Inventory::unequip(std::size_t index){ // can be used with Stuff::StuffType index
    
    if(index >= stuff.size()){
        
        return nullptr;
    }
    
    if(stuff[index]){
        
        Bonus *bonus = stuff[index]->getBonus();
        
        if(addObject(*stuff[index])){
            
            stuff[index].release();
            return bonus;
        }
    }
    
    return nullptr;
}

void Inventory::refillStacks(){}
void Inventory::sort(){}

/*************
 * Accessors *
 *************/

Stuff* Inventory::getStuff(std::size_t index){
    
    return stuff[index].get();
}

Object* Inventory::getObject(std::size_t index){
    
    return bag[index].get();
}

/*************
 * NewObject *
 *************/
Object* newObject(const Object &object){
    
    switch(object.getType()){
        
        case Entity::Stuff:
            return new Stuff(object);
        
        case Entity::StackObject:
            return new StackObject(object);
        
        case Entity::Potion:
            return new Potion(object);
        
        default:
            return new Object(object);
    }
}
