#include "StackObject.h"

StackObject::StackObject(const std::string &name, TextureManager *txtMgr, std::size_t number):
        Object(name, txtMgr),
        number(number){
    
    loadFromFile();
    
    if(number > stackSize){
        
        number = stackSize;
    }

}

std::size_t StackObject::getNumber() const{
    
    return number;
}

std::size_t StackObject::getStackSize() const{
    
    return stackSize;
}

bool StackObject::empty() const{
    
    return (number == 0);
}

StackObject& StackObject::operator+=(std::size_t &toAdd){
    
    std::size_t avail = stackSize - number;
    
    if(toAdd <= avail){
        
        number += toAdd;
        toAdd = 0;
    }
    else{
        number = stackSize;
        toAdd -= avail;
    }
    
    return *this;
}

StackObject& StackObject::operator+=(StackObject &otherStk){
    
    if(name != otherStk.name){
        
        return *this;
    }
    
    return operator+=(otherStk.number);
}

StackObject& StackObject::operator-=(std::size_t &toRemove){
    
    if(toRemove <= number){
        
        number -= toRemove;
        toRemove = 0;
    }
    else{
        number = 0;
        toRemove -= number;
    }
    
    return *this;
}

StackObject& StackObject::operator-=(StackObject &otherStk){
    
    if(name != otherStk.name){
        
        return *this;
    }
    
    return operator-=(otherStk.number);
}

StackObject& StackObject::operator++(){
    
    std::size_t toAdd = 1;
    return operator+=(toAdd);
}

StackObject& StackObject::operator--(){
    
    std::size_t toRemove = 1;
    return operator-=(toRemove);
}

void StackObject::loadFromFile(){
    
    std::string filename = "Data/Files/Objects/" + name + ".cfg";
    
    std::ifstream file(filename);
    if(!file.is_open()){
        
        throw std::runtime_error("Failed to load " + filename);
    }
    
    while(!file.eof()){
        
        std::string line;
        std::getline(file, line);
        std::istringstream sLine(line);
        
        std::string statName;
        int statVal;
        
        sLine >> statName >> statVal;
        
        if(statName == "StackSize"){
            
            stackSize = abs(statVal);
        }
        else if(statName == "BuyPrice"){
            
            buyPrice = statVal;
        }
        else if(statName == "SellPrice"){
            
            sellPrice = statVal;
        }
    }
}

void StackObject::draw(sf::RenderTarget &target, sf::RenderStates states) const{
    
    Object::draw(target, states);
    
    // TODO draw number with sf::Text
}
