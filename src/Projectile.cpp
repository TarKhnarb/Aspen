#include "Projectile.h"

/***************
 * Constructor *
 ***************/
Projectile::Projectile(Character *owner, Orientation orient, TextureManager* txtMng):
        Entity(txtMng, Type::Project),
        owner(owner),
        orientation(orient),
        speed(60.f){ //owner->getFinalValue(ProjectileSpeed)){

    setVelocity();
    selectProjectile();
}

/***************
 * Constructor *
 ***************/
Projectile::~Projectile(){

    textureMgr->releaseResource(textureName);
}

/************
 * GetOwner *
 ************/
Character* Projectile::getOwner(){

    return owner;
}

/**********
 * Update *
 **********/
void Projectile::update(sf::Time time){

    move(velocity * time.asSeconds());
    /*
     * TODO  /!\ TROUVER UNE SOLUTION /!\ :
     * TODO     Lors de la detexion d'une collision, il y a une erreur de segmentation.
     * TODO     Cela ne pose pas de problème lorsque l'on tire à l'OUEST seulement dans les trois autres cas.
     * TODO     Voir si cela ne vient pas de la position de la collisionBox du projectile,
     * TODO     cela pourrait aussi venir de la façon dont j'ai essayé de les gérer.
     */
}

/***************
 * SetVelocity *
 ***************/
void Projectile::setVelocity(){

    float pxMove = 200.f * (1.f + speed/100.f);

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
    spriteProj.setTexture(*textureMgr->getResource(textureName));

    switch(orientation){

        case Orientation::North:
            {
                sf::FloatRect projBox = spriteProj.getGlobalBounds();
                sf::FloatRect ownerBox = owner->getBox();
                if(owner->getType() == Type::Monster){

                    spriteProj.scale(0.5f, 0.5f);
                    spriteProj.setPosition(
                            ownerBox.left + ((ownerBox.width - projBox.width)/2.f),
                            ownerBox.top - (projBox.height + 2.f * ownerBox.height));
                    collisionBox = projBox;
                }
                else{

                    spriteProj.setPosition(
                            ownerBox.left + ((ownerBox.width - projBox.width)/2.f),
                            ownerBox.top - (projBox.height + 2.f * ownerBox.height));
                    collisionBox = projBox;
                    collisionBox.height = collisionBox.height/3.f;
                    std::cout << "North" << std::endl;
                }
            }
            break;

        case Orientation::East:
            {
                spriteProj.setRotation(90.f);
                sf::FloatRect projBox = spriteProj.getGlobalBounds();
                sf::FloatRect ownerBox = owner->getBox();
                if(owner->getType() == Type::Monster){

                    spriteProj.scale(0.5f, 0.5f);
                    spriteProj.setPosition(
                            ownerBox.left + ownerBox.width + projBox.width,
                            ownerBox.top + ((projBox.height - projBox.height)/2.f));
                    collisionBox = projBox;
                }
                else{

                    spriteProj.setPosition(
                            ownerBox.left + ownerBox.width + projBox.width,
                            ownerBox.top + ((projBox.height - projBox.height)/2.f));
                    collisionBox = projBox;
                    collisionBox.width /= 3.f;
                    collisionBox.left += 2.f * collisionBox.width;
                    std::cout << "East" << std::endl;
                }
            }
            break;

        case Orientation::South:
            {
                spriteProj.setRotation(180.f);
                sf::FloatRect projBox = spriteProj.getGlobalBounds();
                sf::FloatRect ownerBox = owner->getBox();
                if(owner->getType() == Type::Monster){

                    spriteProj.scale(0.5f, 0.5f);
                    spriteProj.setPosition(
                            ownerBox.left + ((ownerBox.width + projBox.width)/2.f),
                            ownerBox.top + projBox.height + ownerBox.height);
                    collisionBox = projBox;
                }
                else{

                    spriteProj.setPosition(
                            ownerBox.left + ((ownerBox.width + projBox.width)/2.f),
                            ownerBox.top + projBox.height + ownerBox.height);
                    collisionBox = projBox;
                    collisionBox.height /= 3.f;
                    collisionBox.top += 2.f * collisionBox.height;
                    std::cout << "South" << std::endl;
                }
            }
            break;

        case Orientation::West:
            {
                spriteProj.setRotation(270.f);
                sf::FloatRect projBox = spriteProj.getGlobalBounds();
                sf::FloatRect ownerBox = owner->getBox();
                if(owner->getType() == Type::Monster){

                    spriteProj.scale(0.5f, 0.5f);
                    spriteProj.setPosition(
                            ownerBox.left - projBox.width,
                            ownerBox.top + ((projBox.height + projBox.height)/2.f));
                    collisionBox = projBox;
                }
                else{

                    spriteProj.setPosition(
                            ownerBox.left - projBox.width,
                            ownerBox.top + ((projBox.height + projBox.height)/2.f));
                    collisionBox = projBox;
                    collisionBox.width /= 3.f;
                    collisionBox.left += 2.f * collisionBox.width;
                    std::cout << "West" << std::endl;
                }
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
