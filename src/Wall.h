#ifndef GAME_WALL_H
#define GAME_WALL_H

#include "Entity.h"

class Wall : public Entity{
    
public:
    
    Wall();
    Wall(float x, float y, float Dx, float Dy);
    Wall(sf::FloatRect hitBox);

public:
    
    float& left;
    float& top;
    float& width;
    float& height;
    
private:
    
    void draw(sf::RenderTarget&, sf::RenderStates) const override;
};

#endif
