#include "Potion.h"

Potion::Potion(const std::string &name, TextureManager *txtMgr, std::size_t number):
        StackObject(name, txtMgr, number){
    
    setType(Entity::Potion);
    
    loadFromFile();
}

int Potion::use(std::size_t number){
    
    if(number > getNumber()){
        
        number = getNumber();
    }
    
    *this -= number;
    
    return number * lifeGain;
}

void Potion::loadFromFile(){
    
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
        
        if(statName == "Life"){
            
            lifeGain = statVal;
        }
    }
}
