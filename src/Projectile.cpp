#include "Projectile.h"

/***************
 * Constructor *
 ***************/
Projectile::Projectile(Character *owner, Type type, Orientation orient, float speed, TextureManager*):
        Entity(txtMng, type),
        owner(owner),
        orientation(orient),
        speed(speed),
        baseSpeed(200.f){

    setVelocity();
    selectProjectile();
}

/***************
 * Constructor *
 ***************/
Projectile::~Projectile(){}

/************
 * GetOwner *
 ************/
Character* Projectile::getOwner() const{

    return owner;
}

void Projectile::update(sf::Time time){

    move(velocity * time.asSeconds());
    velocity = sf::Vector2f(0.f, 0.f); // reset velocity for the next update loop
}

/***************
 * SetVelocity *
 ***************/
void Projectile::setVelocity(){

    float pxMove = baseSpeed * (1.f + speed/60.f);

    switch(orientation){
        case Orientation::North:
            velocity.y -= pxMove;
            break;

        case Orientation::East:
            velocity.x += pxMove;
            break;

        case Orientation::South:
            velocity.y += pxMove;
            break;

        case Orientation::West:
            velocity.x -= pxMove;
            break;

        default:
            break;
    }
    /*if(velocity.x != 0.f && velocity.y != 0.f){ // diagonal movement

        velocity /= static_cast<float>(sqrt(2.f)); // normalize vector
    }*/ // Activate when 8 orientation
}

/********************
 * SelectProjectile *
 ********************/
void Projectile::selectProjectile(){

    textureName = (owner->getType() == Type::Monster) ? "MonsterProjectile" : "PlayerProjectile";

    textureMgr->requireResource(textureName);
    spriteProf.setTexture(*textureMgr->getResource(textureName));

    sf::FloatRect projBox = spriteProf.getLocalBounds();
    sf::FloatRect ownerBox = owner->getGlobalBounds();

    switch(orientation){

        case Orientation::North:

            sf::FloatRect projBox = spriteProf.getGlobalBounds();
            sf::FloatRect ownerBox = owner->getGlobalBounds();
            if(owner->getType() == Type::Monster){

                spriteProf.scale(0.5f, 0.5f);
                spriteProf.setPosition(
                        ownerBox.left + ((ownerBox.width - projBox.width)/2.f),
                        ownerBox.top + projBox.height);
                collisionBox = projBox;
            }
            else{

                spriteProf.setPosition(
                        ownerBox.left + ((ownerBox.width - projBox.width)/2.f),
                        ownerBox.top + projBox.height);
                collisionBox = projBox;
                collisionBox.height /= 3.f;
            }
            break;

        case Orientation::East:

            spriteProf.setRotation(90.f);
            sf::FloatRect projBox = spriteProf.getGlobalBounds();
            sf::FloatRect ownerBox = owner->getGlobalBounds();
            if(owner->getType() == Type::Monster){

                spriteProf.scale(0.5f, 0.5f);
                spriteProf.setPosition(
                        ownerBox.left + ownerBox.width + projBox.width,
                        ownerBox.top + ((projBox.height + projBox.height)/2.f));
                collisionBox = projBox;
            }
            else{

                spriteProf.setPosition(
                        ownerBox.left + ownerBox.width + projBox.width,
                        ownerBox.top + ((projBox.height + projBox.height)/2.f));
                collisionBox = projBox;
                collisionBox.width /= 3.f;
                collisionBox.left += 2.f * collisionBox.width;
            }
            break;

        case Orientation::South:

            spriteProf.setRotation(180.f);
            sf::FloatRect projBox = spriteProf.getGlobalBounds();
            sf::FloatRect ownerBox = owner->getGlobalBounds();
            if(owner->getType() == Type::Monster){

                spriteProf.scale(0.5f, 0.5f);
                spriteProf.setPosition(
                        ownerBox.left + ((ownerBox.width - projBox.width)/2.f),
                        ownerBox.top + projBox.height);
                collisionBox = projBox;
            }
            else{

                spriteProf.setPosition(
                        ownerBox.left + ((ownerBox.width - projBox.width)/2.f),
                        ownerBox.top + projBox.height);
                collisionBox = projBox;
                collisionBox.height /= 3.f;
                collisionBox.top += 2.f * collisionBox.height;
            }
            break;

        case Orientation::West:

            spriteProf.setRotation(270.f);
            sf::FloatRect projBox = spriteProf.getGlobalBounds();
            sf::FloatRect ownerBox = owner->getGlobalBounds();
            if(owner->getType() == Type::Monster){

                spriteProf.scale(0.5f, 0.5f);
                spriteProf.setPosition(
                        ownerBox.left + ownerBox.width + projBox.width,
                        ownerBox.top + ((projBox.height + projBox.height)/2.f));
                collisionBox = projBox;
            }
            else{

                spriteProf.setPosition(
                        ownerBox.left + ownerBox.width + projBox.width,
                        ownerBox.top + ((projBox.height + projBox.height)/2.f));
                collisionBox = projBox;
                collisionBox.width /= 3.f;
                collisionBox.left += 2.f * collisionBox.width;
            }
            break;

        default:
            break;
    }
}

/********
 * Draw *
 ********/
void Projectile::draw(sf::RenderTarget &target, sf::RenderStates states) const{

    states.transform *= getTransform();
    target.draw(spriteProj, states);
}