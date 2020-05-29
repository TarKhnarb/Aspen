#include "Virus.h"

Virus::Virus(Character *target, TextureManager* txtMgr):
    Monster("Virus", target, txtMgr),
    stateTime(sf::Time::Zero),
    isMoving(false),
    dashesNb(0u),
    travelled(0.f){
        
    calculateDestination();
}

Virus::~Virus(){}

void Virus::update(sf::Time dt){
    
    stateTime += dt;
    
    // updating state
    if(isMoving && dashesNb >= 2.f){
        
        isMoving = false;
        stateTime = sf::Time::Zero;
        velocity = sf::Vector2f(0.f, 0.f);
    }
    else if(!isMoving && stateTime > sf::seconds(2.f)){
        
        stateTime -= sf::seconds(2.f);
        dt -= stateTime; // adapt dt to avoid teleport when virus starts dashing
        stateTime = sf::Time::Zero;
        
        isMoving = true;
        dashesNb = 0u;
        
        calculateDestination();
    }
    
    // update velocity
    
    if(isMoving){
        
        sf::Vector2f realMove = velocity * dt.asSeconds();
        move(realMove);
        
        float distance = sqrt(realMove.x * realMove.x + realMove.y * realMove.y);
        travelled += distance;
        
        if(travelled >= 100.f * (1.f + stats.getFinalValue(Speed)/100.f)){
            
            ++dashesNb;
            
            calculateDestination();
        }
    }
}

Projectile* Virus::getProjectile(){
    
    return nullptr;
}

sf::Vector2f Virus::getDistance() const{
    
    sf::FloatRect thisBox = getBox();
    sf::Vector2f thisCenter;
    
    thisCenter.x = thisBox.left + thisBox.width / 2.f;
    thisCenter.y = thisBox.top + thisBox.height / 2.f;
    
    sf::FloatRect targetBox = target->getBox();
    sf::Vector2f targetCenter;
    
    targetCenter.x = destination.x + targetBox.width / 2.f;
    targetCenter.y = destination.y + targetBox.height / 2.f;
    
    return targetCenter - thisCenter;
}

void Virus::calculateDestination(){
    
    travelled = 0.f;
    
    destination = target->getPosition();
    
    sf::Vector2f direction = getDistance();
    direction /= static_cast<float>(sqrt(direction.x * direction.x + direction.y * direction.y)); // normalize the vector
    
    velocity = direction * getBaseSpeed() * (1.f + stats.getFinalValue(Speed)/100.f); // move
}
