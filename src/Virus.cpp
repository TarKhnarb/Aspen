#include "Virus.h"

Virus::Virus(Character *target, TextureManager* txtMgr):
    Monster("Virus", target, txtMgr),
    stateTime(sf::Time::Zero),
    isMoving(false),
    dashesNb(0u){
        
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
        
        move(velocity);
        
        sf::Vector2f dist = getDistance();
        float fDist = sqrt(dist.x * dist.x + dist.y * dist.y);
        
        if(fDist <= 8.f){ // totally arbitrary
            
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
    
    destination = target->getPosition();
    
    direction = getDistance();
    direction /= (direction.x * direction.x + direction.y * direction.y); // normalize the vector
    
    velocity = direction * getBaseSpeed() * (1.f + stats.getFinalValue(Speed)/100.f); // move
}
