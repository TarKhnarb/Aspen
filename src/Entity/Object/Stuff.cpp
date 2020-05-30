#include "Stuff.h"

Stuff::Stuff(const std::string &name, TextureManager* txtMgr):
        Object(name, txtMgr){
            
            loadFromFile(name);
}

void Stuff::loadFromFile(const std::string &name){
    
    //Object::loadFromFile(name); // TODO create the function
    
    // TODO convert name into filename
    // TODO load type and bonus
}

Stuff::StuffType Stuff::getStuffType() const{
    
    return stuffType;
}

Bonus* Stuff::getBonus(){
    
    return &bonus;
}
