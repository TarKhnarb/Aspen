#ifndef GAME_STATISTICS_H
#define GAME_STATISTICS_H

#include <vector>
#include <array>

#include "Bonus.h"

class Statistics{
    
public:
    
    friend class Bonus;
    
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
