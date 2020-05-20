#include "Statistics.h"

Statistics::Statistics(){
    
    values.fill(1.f);
}

Statistics::Statistics(const std::string& filename){
    
    loadFromFile(filename);
}

void Statistics::loadFromFile(const std::string& filename){
    
    std::ifstream file(filename);
    
    if(!file.is_open()){
        throw std::runtime_error("Statistics::loadFromFile() - Failed to load " + filename);
    }
    
    std::size_t statNum = 0;
    while(!file.eof()){
        
        std::string line;
        std::getline(file, line);
        std::stringstream sLine(line);
        
        std::string statName;
        sLine >> statName >> values[statNum];
            
        ++statNum;
    }
    
    file.close();
}

float Statistics::getBaseValue(StatName stat) const{
    
    return values[stat];
}

float Statistics::getFinalValue(StatName stat) const{
    
    sf::Vector2f modif(0.f, 1.f);
    
    for(Bonus *bonus : bonuses){
        
        sf::Vector2f values = bonus->getValues(stat);
        modif.x += values.x;
        modif.y *= values.y;
    }
    
    return (getBaseValue(stat) + modif.x) * modif.y;
}

void Statistics::addBonus(Bonus *bonus){
    
    if(bonus){
        
        bonuses.push_back(bonus);
    }
}

void Statistics::removeBonus(Bonus *bonus){
    
    auto found = std::find(bonuses.begin(), bonuses.end(), bonus);
    bonuses.erase(found);
}
