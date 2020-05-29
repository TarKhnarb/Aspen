#include "Player.h"
#include "StateManager.h"

/***************
 * Constructor *
 ***************/
Player::Player(TextureManager *txtMng, EventManager* evtMgr):
        Character("Aspen", Type::Player, txtMng),
        spriteSheet(txtMng),
        evtMgr(evtMgr),
        timeSinceShot(sf::Time::Zero),
        projHorizontal(0),
        projVertical(0),
        dungeon(nullptr){

    spriteSheet.loadSheet("Data/Files/SpriteSheets/PlayerSheet.sprite");
    
    sf::Vector2f size = spriteSheet.getSpriteSize();
    
    collisionBox.width = size.x;
    collisionBox.top = 5/6.f * size.y;
    collisionBox.height = 1/3.f * size.y;
    
    evtMgr->addCallback(StateType::Dungeon, "MoveUp", &Player::setVelocity, this);
    evtMgr->addCallback(StateType::Dungeon, "MoveRight", &Player::setVelocity, this);
    evtMgr->addCallback(StateType::Dungeon, "MoveDown", &Player::setVelocity, this);
    evtMgr->addCallback(StateType::Dungeon, "MoveLeft", &Player::setVelocity, this);

    evtMgr->addCallback(StateType::Map, "MoveUp", &Player::setVelocity, this);
    evtMgr->addCallback(StateType::Map, "MoveRight", &Player::setVelocity, this);
    evtMgr->addCallback(StateType::Map, "MoveDown", &Player::setVelocity, this);
    evtMgr->addCallback(StateType::Map, "MoveLeft", &Player::setVelocity, this);

    evtMgr->addCallback(StateType::Dungeon, "ShootUp", &Player::setProjectile, this);
    evtMgr->addCallback(StateType::Dungeon, "ShootRight", &Player::setProjectile, this);
    evtMgr->addCallback(StateType::Dungeon, "ShootDown", &Player::setProjectile, this);
    evtMgr->addCallback(StateType::Dungeon, "ShootLeft", &Player::setProjectile, this);
}

/**************
 * Destructor *
 **************/
Player::~Player(){
    
    evtMgr->removeCallback(StateType::Dungeon, "MoveUp");
    evtMgr->removeCallback(StateType::Dungeon, "MoveRight");
    evtMgr->removeCallback(StateType::Dungeon, "MoveDown");
    evtMgr->removeCallback(StateType::Dungeon, "MoveLeft");
    
    evtMgr->removeCallback(StateType::Map, "MoveUp");
    evtMgr->removeCallback(StateType::Map, "MoveRight");
    evtMgr->removeCallback(StateType::Map, "MoveDown");
    evtMgr->removeCallback(StateType::Map, "MoveLeft");

    evtMgr->removeCallback(StateType::Map, "ShootUp");
    evtMgr->removeCallback(StateType::Map, "ShootRight");
    evtMgr->removeCallback(StateType::Map, "ShootDown");
    evtMgr->removeCallback(StateType::Map, "ShootLeft");
}

/**********
 * Update *
 **********/
void Player::update(sf::Time time){
    
    if(velocity.x != 0.f && velocity.y != 0.f){ // diagonal movement
        
        velocity /= static_cast<float>(sqrt(2.f)); // normalize vector
    }

    move(velocity * time.asSeconds());
    
    animate();
    spriteSheet.update(time.asSeconds() * (1.f + stats.getFinalValue(Speed)/100.f)); // accelerates anim
    
    timeSinceShot += time;

    velocity = sf::Vector2f(0.f, 0.f); // reset velocity for the next update loop
}

/**************
 * ChangeRoom *
 **************/
void Player::changeRoom(Orientation orient){

    std::string filePath = "Data/Files/Dungeon/PlayerCoordinates.cfg";
    std::ifstream file;
    file.open(filePath);

    float x, y;

    if(file.is_open()) {

        std::string line;
        for(int i = 0; i < static_cast<int>(orient) + 1; ++i){

            if(file.eof())
                throw std::runtime_error("Failed to load position for orientation : " + std::to_string(static_cast<int>(orient)));

            getline(file, line);
        }

        std::istringstream iss(line);
        x = static_cast<float>(returnStoi(iss));
        y = static_cast<float>(returnStoi(iss));

    }
    else
        throw std::runtime_error ("Failed to load " + filePath);

    file.close();

    setPosition(x, y);
}

/**************
 * SetDungeon *
 **************/
void Player::setDungeon(Dungeon *dunge){

    dungeon = dunge;
}

/*****************
 * SetProjectile *
 *****************/
void Player::setProjectile(EventDetails *details){

    if (details->name == "ShootUp"){
        
        if (projVertical > -1)
            --projVertical;
    }
    else if (details->name == "ShootRight"){
        
        if(projHorizontal < 1)
            ++projHorizontal;
    }
    else if (details->name == "ShootDown"){
        
        if(projVertical < 1)
            ++projVertical;
    }
    else if (details->name == "ShootLeft"){
        
        if(projHorizontal > -1)
            --projHorizontal;
    }
}

Projectile* Player::getProjectile(){
    
    if(timeSinceShot.asSeconds() < 60.f / stats.getFinalValue(AttackSpeed)){
        
        projHorizontal = 0;
        projVertical = 0;

        return nullptr;
    }

    Orientation projOrientation = Orientation::None;
    
    switch(projHorizontal){
        
        case -1:
            switch(projVertical){
                
                case -1:
                    projOrientation = Orientation::NorthWest;
                    break;
                
                case 0:
                    projOrientation = Orientation::West;
                    break;
                
                case 1:
                    projOrientation = Orientation::SouthWest;
                    break;
                
                default:
                    break;
            }
            break;
        
        case 0:
            switch(projVertical){
                
                case -1:
                    projOrientation = Orientation::North;
                    break;
                
                case 0:
                    break;
                
                case 1:
                    projOrientation = Orientation::South;
                    break;
                
                default:
                    break;
            }
            break;
        
        case 1:
            switch(projVertical){
                
                case -1:
                    projOrientation = Orientation::NorthEast;
                    break;
                
                case 0:
                    projOrientation = Orientation::East;
                    break;
                
                case 1:
                    projOrientation = Orientation::SouthEast;
                    break;
                
                default:
                    break;
            }
            break;
        
        default:
            break;
    }
    
    projHorizontal = 0;
    projVertical = 0;
    
    if(projOrientation == Orientation::None){
        
        return nullptr;
    }
    
    timeSinceShot = sf::Time::Zero;
    return new Projectile(this, projOrientation, textureMgr);
}

/**************
 * ReturnStoi *
 **************/
int Player::returnStoi(std::istringstream &ss){

    std::string result;
    std::getline(ss, result, ',');
    return std::stoi(result);
}

/***************
 * SetVelocity *
 ***************/
void Player::setVelocity(EventDetails *details){
    
    float pxMove = getBaseSpeed() * (1.f + stats.getFinalValue(Speed)/100.f);
    
    if(details->name == "MoveUp"){
        
        velocity.y -= pxMove;
    }
    if(details->name == "MoveRight"){
        
        velocity.x += pxMove;
    }
    if(details->name == "MoveDown"){
        
        velocity.y += pxMove;
    }
    if(details->name == "MoveLeft"){
        
        velocity.x -= pxMove;
    }
}

/********
 * Draw *
 ********/
void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const{

    states.transform *= getTransform();
    target.draw(spriteSheet, states);
}

/***********
 * Animate *
 ***********/
void Player::animate(){

    if(velocity.x != 0.f || velocity.y != 0.f){

        if(velocity.y < 0.f && abs(velocity.y) > abs(velocity.x)){
            
            spriteSheet.setAnimation("Moving", true, true);
            spriteSheet.setOrientation(Orientation::North);
        }

        else if(velocity.x > 0.f && abs(velocity.x) >= abs(velocity.y)){
            
            spriteSheet.setAnimation("Moving", true, true);
            spriteSheet.setOrientation(Orientation::East);
        }

        else if(velocity.y > 0.f && abs(velocity.y) > abs(velocity.x)){
            
            spriteSheet.setAnimation("Moving", true, true);
            spriteSheet.setOrientation(Orientation::South);
        }

        else if(velocity.x < 0.f && abs(velocity.x) >= abs(velocity.y)){
            
            spriteSheet.setAnimation("Moving", true, true);
            spriteSheet.setOrientation(Orientation::West);
        }
    }
    else{
        
        spriteSheet.setAnimation("Idle", false, false);
        spriteSheet.setOrientation(Orientation::South);
    }
}
