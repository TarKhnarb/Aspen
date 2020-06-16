#include "Stuff.h"

/***************
 * Constructor *
 ***************/
Stuff::Stuff(const std::string &name, TextureManager* txtMgr):
        Object(name, txtMgr){

    loadFromFile();
}

/***************
 * Constructor *
 ***************/
Stuff::Stuff(Object *obj):
        Object(obj->getName(), getTextureManager()),
        object(obj){

    Stuff(object->getName(), getTextureManager());
}

/**************
 * Destructor *
 **************/
Stuff::~Stuff(){

    if(object)
        delete object;
}

void Stuff::loadFromFile(){

    std::string filename = "Data/Files/Objects/" + name + ".cfg";

    std::ifstream file(filename);
    if(!file.is_open())
        throw std::runtime_error("Failed to load " + filename);

    while(!file.eof()){

        std::string line;
        std::getline(file, line);
        std::istringstream sLine(line);

        std::string statName;
        std::string statVal;

        sLine >> statName >> statVal;

        if(statName == "Type"){

            if(statVal == "Weapon")
                stuffType = Weapon;
            else if(statVal == "Helmet")
                stuffType = Helmet;
            else if(statVal == "Amulet")
                stuffType = Amulet;
            else if(statVal == "ChestPlate")
                stuffType = ChestPlate;
            else if(statVal == "Leggings")
                stuffType = Leggings;
            else if(statVal == "Boots")
                stuffType = Boots;
        }
    }
}

Stuff::StuffType Stuff::getStuffType() const{
    
    return stuffType;
}