#ifndef WALL_H
#define WALL_H

#include "Entity.h"

class Wall : public Entity{
    
public:
    
    Wall();
    
    float& left;
    float& top;
    float& width;
    float& height;
    
private:
    
    void draw(sf::RenderTarget&, sf::RenderStates) const override;
};

#endif
