#include "Stuff.h"

/***************
 * Constructor *
 ***************/
Stuff::Stuff(Object *object):
        Object(*object){

    loadFromFile();
    setSprite();
}

/****************
 * LoadFromFile *
 ****************/
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

void Stuff::draw(sf::RenderTarget& target, sf::RenderStates states) const{

    states.transform *= getTransform();
    target.draw(sprite, states);
}

/*************
 * SetSprite *
 *************/
void Stuff::setSprite(){

    textureMgr->requireResource(name);
    sprite.setTexture(*textureMgr->getResource(name));

    collisionBox = sprite.getGlobalBounds();
}

/****************
 * GetStuffType *
 ****************/
Stuff::StuffType Stuff::getStuffType() const{
    
    return stuffType;
}