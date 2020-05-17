#include "Player.h"

Player::Player(TextureManager *txtMng):
        Character("Aspen", Type::Player, txtMng),
        spriteSheet(txtMng){

    aspen.loadSheet("Data/Files/SpriteSheets/PlayerSheet.sprite");

    speed = 5.f;
    velocity = {50.f, 50.f};
}

Player::~Player(){

}

void Player::update(sf::Time time){

    sf::Vector2f vector(0.f, 0.f);

    if (EventDetails::name == "MoveUp") {

        vector = sf::Vector2f(0.f, -increment.y);
    }
    if (EventDetails::name == "MoveRight") {

        vector = sf::Vector2f(increment.x, 0.f);
    }
    if (EventDetails::name == "MoveDown") {

        vector = sf::Vector2f(0.f, increment.y);
    }
    if (EventDetails::name == "MoveLeft") {

        vector = sf::Vector2f(-increment.x, 0.f);
    }

    animate(vector);
    aspen.update(time);
    aspen.setSpritePosition(vector * velocity * (speed/10.f));
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states){

    states.transform *= getTransform();
    target.draw(aspen, states);
}

void Party::animate(sf::Vector2f vector){

    if(vector != {0.f, 0.f}){

        if(vector == {0.f, -increment.y})
            aspen.setAnimation("Up", true, true);

        else if(vector == {increment.x, 0.f})
            aspen.setAnimation("Right", true, true);

        else if(vector == {0.f, increment.y})
            aspen.setAnimation("Down", true, true);

        else if(vector == {-increment.x, 0.f})
            aspen.setAnimation("Left", true, true);
    }
}