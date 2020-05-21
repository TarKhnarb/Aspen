#ifndef GAME_STACKOBJECT_H
#define GAME_STACKOBJECT_H

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cmath>

#include "Object.h"

class StackObject : public Object{
    
public:
    
    StackObject() = delete;
    StackObject(const std::string&, TextureManager*, std::size_t = 0);
    
public:
    
    std::size_t getNumber() const;
    std::size_t getStackSize() const;
    bool empty() const;
    
    StackObject& operator+=(std::size_t&);
    StackObject& operator+=(StackObject&);
    StackObject& operator-=(std::size_t&);
    StackObject& operator-=(StackObject&);
    StackObject& operator++();
    StackObject& operator--();
    
private:
    
    void loadFromFile();
    
    void draw(sf::RenderTarget&, sf::RenderStates) const override;
    
private:
    
    std::size_t number;
    std::size_t stackSize;
};

#endif
p
