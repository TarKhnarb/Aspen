#include "LittleDeath.h"

LittleDeath::LittleDeath(Character *target, TextureManager *txtMgr):
        Monster("LittleDeath", target, txtMgr),
        stateTime(sf::Time::Zero),
        isMoving(false),
        movesNb(0u),
        shootsNb(0u),
        travelled(0.f){

    calculateDestination();
}

LittleDeath::~LittleDeath(){}

void LittleDeath::update(sf::Time dt){

    stateTime += dt;

    // updating state
    if(isMoving && movesNb >= 2.f){

        isMoving = false;
        stateTime = sf::Time::Zero;
        velocity = sf::Vector2f(0.f, 0.f);

        for(unsigned i = 0; i < 4; ++i){

            this->setProjectile()
        }
    }
    else if(!isMoving && stateTime > sf::seconds(1.5f)){

        stateTime -= sf::seconds(1.5f);
        dt -= stateTime; // adapt dt to avoid teleport when virus starts dashing
        stateTime = sf::Time::Zero;

        isMoving = true;
        movesNb = 0u;

        calculateDestination();
    }

    // update velocity

    if(isMoving){

        sf::Vector2f realMove = velocity * dt.asSeconds();
        move(realMove);

        travelled += 50.f;

        if(travelled <= 100.f * (1.f + stats.getFinalValue(Speed)/100.f)){

            ++movesNb;
            calculateDestination();
        }
    }
}

/*****************
 * SetProjectile *
 *****************/
void LittleDeath::setProjectile(){

    std::vector<std::vector<unique_ptr<Projectile>>> projectiles;

    for(unsigned i = 0; i < shootsNb; ++i){

        projectiles.push_back(getProjectile());
    }
}

std::vector<unique_ptr<Projectile>> LittleDeath::getProjectile(){

    std::vector<unique_ptr<Projectile>> projectiles;
    for(unsiqued i = 0; i < 8; ++i){

        std::unique_ptr<Projectile> proj = new Projectile(this, i, textureMgr);
        projectiles.push_back(std::move(proj));
    }
    return projectiles;
}

sf::Vector2f LittleDeath::getDistance() const{ // TODO à OPTIMISER

    sf::FloatRect thisBox = getBox();
    sf::Vector2f thisCenter;

    thisCenter.x = thisBox.left + thisBox.width / 2.f;
    thisCenter.y = thisBox.top + thisBox.height / 2.f;

    sf::FloatRect targetBox = target->getBox();
    sf::Vector2f targetCenter;

    targetCenter.x = destination.x + targetBox.width / 2.f;
    targetCenter.y = destination.y + targetBox.height / 2.f;

    if(std::abs(targetCenter.x - thisCenter.x) > std::abs(targetCenter.y = thisCenter.y)){

        //y
        float delta = targetCenter.y - thisCenter.y;
        if(delta >= 0.f){

            if(delta <= 50.f)
                return {0.f, delta}; // On se centre par rapport au joueur
            else
                return {0.f, 50.f}; // On se déplace le plus possible dans sa direction
        }
        else{ // delta < 0.f

            if(delta >= -50.f)
                return {0.f, delta};
            else
                return {0.f, -50.f};
        }
    }
    else{

        //x
        float delta = targetCenter.x - thisCenter.x;
        if(delta >= 0.f){

            if(delta <= 50.f)
                return {delta, 0.f}; // On se centre par rapport au joueur
            else
                return {50.f, 0.f}; // On se déplace le plus possible dans sa direction
        }
        else{ // delta < 0.f

            if(delta >= -50.f)
                return {delta, 0.f};
            else
                return {-50.f, 0.f};
        }
    }
}

void LittleDeath::calculateDestination(){

    travelled = 0.f;

    destination = target->getPosition();

    sf::Vector2f direction = getDistance();
    direction /= static_cast<float>(sqrt(direction.x * direction.x + direction.y * direction.y)); // normalize the vector

    velocity = direction * getBaseSpeed() * (1.f + stats.getFinalValue(Speed)/100.f); // move
}