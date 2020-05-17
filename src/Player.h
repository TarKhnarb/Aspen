#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

//#include "EventManager.h"

class Player: public Character, public EventDetails{

public:

    Player(TextureManager*);
    ~Player();

public:

    void update(sf::Time time);


private:

    void draw(sf::RenderTarget&, sf::RenderStates);

    void animate();


private:

    SpriteSheet aspen;
    sf::FloatRect;

    float speed;

    sf::Vector2f velocity;
};

#endif