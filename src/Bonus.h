#ifndef GAME_BONUS_H
#define GAME_BONUS_H

#include <array>
#include <string>
#include <SFML/System/Vector2.hpp>

enum StatName{
    
    Life,
    MaxLife,
    Attack,
    AttackSpeed,
    ProjectileSpeed,
    Defence,
    Speed,
    CanFly,
    StatCount
};

class Bonus{
    
public:
    
    Bonus();
    Bonus(const std::string&);
    
public:
    
    void loadFromFile(const std::string&);
    
    sf::Vector2f getValues(StatName) const;
    
private:
    
    std::array<float, StatCount> absolute;
    std::array<float, StatCount> relative;
};

#endif
