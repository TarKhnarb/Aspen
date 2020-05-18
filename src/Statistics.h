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
    
    float getBaseValue(StatName) const;
    float getFinalValue(StatName) const;
    
    void addBonus(Bonus*);
    void removeBonus(Bonus*);
    
private:
    
    std::array<float, StatCount> values;
    std::vector<Bonus*> bonuses;
};

#endif
