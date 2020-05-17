#include "Player.h"
#include "StateManager.h"

Player::Player(TextureManager *txtMng, EventManager* evtMgr):
        Character("Aspen", Type::Player, txtMng),
        aspen(txtMng),
        evtMgr(evtMgr){

    aspen.loadSheet("Data/Files/SpriteSheets/PlayerSheet.sprite");

    speed = 300.f;
    
    sf::Vector2f size = aspen.getSpriteSize();
    collisionBox.width = size.x;
    collisionBox.top = 2/3.f * size.y;
    collisionBox.height = 1/3.f * size.y;
    
    evtMgr->addCallback(StateType::Dungeon, "MoveUp", &Player::setVelocity, this);
    evtMgr->addCallback(StateType::Dungeon, "MoveRight", &Player::setVelocity, this);
    evtMgr->addCallback(StateType::Dungeon, "MoveDown", &Player::setVelocity, this);
    evtMgr->addCallback(StateType::Dungeon, "MoveLeft", &Player::setVelocity, this);
}

Player::~Player(){
    
    evtMgr->removeCallback(StateType::Dungeon, "MoveUp");
    evtMgr->removeCallback(StateType::Dungeon, "MoveRight");
    evtMgr->removeCallback(StateType::Dungeon, "MoveDown");
    evtMgr->removeCallback(StateType::Dungeon, "MoveLeft");
}

void Player::update(sf::Time time){

    move(velocity * time.asSeconds());
    
    animate();
    aspen.update(time.asSeconds());
    
    velocity = sf::Vector2f(0.f, 0.f); // reset velocity for the next update loop
}

void Player::setVelocity(EventDetails* details){
    
    if (details->name == "MoveUp"){
        
        velocity.y -= speed;
    }
    if (details->name == "MoveRight"){
        
        velocity.x += speed;
    }
    if (details->name == "MoveDown"){
        
        velocity.y += speed;
    }
    if (details->name == "MoveLeft"){
        
        velocity.x -= speed;
    }
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const{

    states.transform *= getTransform();
    target.draw(aspen, states);
}

void Player::animate(){

    if(velocity.x != 0.f || velocity.y != 0.f){

        if(velocity.y < 0.f && abs(velocity.y) > abs(velocity.x))
            aspen.setAnimation("Up", true, true);

        else if(velocity.x > 0.f && abs(velocity.x) >= abs(velocity.y))
            aspen.setAnimation("Right", true, true);

        else if(velocity.y > 0.f && abs(velocity.y) > abs(velocity.x))
            aspen.setAnimation("Down", true, true);

        else if(velocity.x < 0.f && abs(velocity.x) >= abs(velocity.y))
            aspen.setAnimation("Left", true, true);
    }
    else{
        
        aspen.setAnimation("Idle", true, false);
    }
}
