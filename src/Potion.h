#ifndef GAME_POTION_H
#define GAME_POTION_H

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cmath>

#include "StackObject.h"

class Potion : public StackObject{
    
public:
    
    Potion() = delete;
    Potion(const std::string&, TextureManager*, std::size_t = 0);
    
public:
    
    int use(std::size_t = 1);
    
private:
    
    void loadFromFile();
    
private:
    
    int lifeGain;
};

#endif
