#include "Bonus.h"

/***************
 * Constructor *
 ***************/
Bonus::Bonus(){
    
    absolute.fill(0.f);
    relative.fill(1.f);
}

/***************
 * Constructor *
 ***************/
Bonus::Bonus(const std::string &filename){
    
    loadFromFile(filename);
}

/****************
 * LoadFromFile *
 ****************/
void Bonus::loadFromFile(const std::string &filename){
    
    // TODO
}

/*************
 * GetValues *
 *************/
sf::Vector2f Bonus::getValues(StatName stat) const{
    
    sf::Vector2f values;
    
    values.x = absolute[stat];
    values.y = relative[stat];
    
    return values;
}
