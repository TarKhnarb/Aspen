#ifndef GAME_STATISTICS_H
#define GAME_STATISTICS_H

#include <vector>
#include <array>
#include <string>
#include <algorithm>
#include <fstream>
#include <stdexcept>
#include <sstream>

#include "Bonus.h"

class Statistics{
    
public:
    
    Statistics();
    Statistics(const std::string&);
    
public:
    
    void loadFromFile(const std::string&);
    
    void resetLife();
    void modify(StatName, float);
    
    float getBaseValue(StatName) const;
    float getFinalValue(StatName) const;
    
    void addBonus(Bonus*);
    void removeBonus(Bonus*);
    
private:
    
    void updateFinal();
    void updateBase();
    
private:
    
    std::array<float, StatCount> values;
    std::array<float, StatCount> finals;
    std::vector<Bonus*> bonuses;
};

#endif
