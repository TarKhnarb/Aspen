#include "Statistics.h"

/***************
 * Constructor *
 ***************/
Statistics::Statistics(){
    
    values.fill(1.f);
    
    updateFinal();
}

/***************
 * Constructor *
 ***************/
Statistics::Statistics(const std::string &filename){
    
    loadFromFile(filename);
    
    updateFinal();
}

/****************
 * LoadFromFile *
 ****************/
void Statistics::loadFromFile(const std::string &filename){
    
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

void Statistics::resetLife(){
    
    values[Life] = values[MaxLife];
}

void Statistics::modify(StatName stat, float modif){
    
    finals[stat] += modif;
    
    // TODO cap here
    
    updateBase();
}

/****************
 * GetBaseValue *
 ****************/
float Statistics::getBaseValue(StatName stat) const{
    
    return values[stat];
}

/*****************
 * GetFinalValue *
 *****************/
float Statistics::getFinalValue(StatName stat) const{
    
    return finals[stat];
}

/************
 * AddBonus *
 ************/
void Statistics::addBonus(Bonus *bonus){
    
    if(bonus){
        
        bonuses.push_back(bonus);
    }
    
    updateFinal();
}

/***************
 * RemoveBonus *
 ***************/
void Statistics::removeBonus(Bonus *bonus){
    
    auto found = std::find(bonuses.begin(), bonuses.end(), bonus);
    bonuses.erase(found);
    
    updateFinal();
}

void Statistics::updateFinal(){
    
    for(std::size_t i = 0; i < StatCount; ++i){
        
        sf::Vector2f modif(0.f, 1.f);
        
        for(Bonus *bonus : bonuses){
            
            sf::Vector2f values = bonus->getValues(static_cast<StatName>(i));
            modif.x += values.x;
            modif.y *= values.y;
        }
        
        finals[i] = (getBaseValue(static_cast<StatName>(i)) + modif.x) * modif.y;
        
        // TODO cap here
    }
}

void Statistics::updateBase(){
    
    for(std::size_t i = 0; i < StatCount; ++i){
        
        sf::Vector2f modif(0.f, 1.f);
        
        for(Bonus *bonus : bonuses){
            
            sf::Vector2f values = bonus->getValues(static_cast<StatName>(i));
            modif.x += values.x;
            modif.y *= values.y;
        }
        
        values[i] = (getFinalValue(static_cast<StatName>(i)) / modif.y) - modif.x;
        
        // TODO cap here
    }
}

/*
 * TODO cap functions
 * 
 * inspiration: 
 * 
 * switch(stat){
        
        case Life:
            
            if(values[Life] < 0.f){
                
                values[Life] = 0.f;
            }
            if(values[Life] >= values[MaxLife]){
                
                values[Life] = values[MaxLife];
            }
            break,
        
        case MaxLife:
            
            if(values[MaxLife] < 0.f){
                
                values[MaxLife] = 0.f;
            }
            break;
        
        case AttackSpeed:
            
            if(values[AttackSpeed] < 1.f){
                
                values[AttackSpeed] = 1.f;
            }
            break;
        
        case CanFly:
            
            if(values[CanFly] < 0.f){
                
                values[CanFly] = 0.f;
            }
            else if(values[CanFly] > 1.f){
                
                values[CanFly] = 1.f;
            }
            break;
            
        default:
            break;
    */
