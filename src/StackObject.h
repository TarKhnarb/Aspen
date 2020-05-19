#ifndef GAME_STACKOBJECT_H
#define GAME_STACKOBJECT_H

#include "Object.h"

class StackObject : public Object{
    
public:
    
    StackObject() = delete;
    StackObject(const std::string&, TextureManager*, std::size_t = 0);
    
public:
    
    void loadFromFile(const std::string&);
    
    std::size_t getNumber() const;
    std::size_t getStackSize() const;
    bool empty() const;
    
    StackObject& operator+=(std::size_t& number);
    StackObject& operator+=(const StackObject&);
    StackObject& operator-=(std::size_t& number);
    StackObject& operator-=(const StackObject&);
    StackObject& operator++();
    StackObject& operator--();
    
private:
    
    void draw(sf::RenderTarget&, sf::RenderStates) const override; // TODO add number in left bot corner
    
private:
    
    std::size_t number;
    std::size_t stackSize;
};

StackObject& operator+(const StackObject&, const StackObject&);

#endif
