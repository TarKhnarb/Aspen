#include "Player.h"
#include "StateManager.h"

Player::Player(TextureManager *txtMng, EventManager* evtMgr):
        Character("Aspen", Type::Player, txtMng),
        spritesheet(txtMng),
        stats("Data/Files/Characters/Aspen.cfg"),
        baseSpeed (150.f),
        evtMgr(evtMgr){

    spritesheet.loadSheet("Data/Files/SpriteSheets/PlayerSheet.sprite");
    
    
    sf::Vector2f size = spritesheet.getSpriteSize();
    
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
}

Player::~Player(){
    
    evtMgr->removeCallback(StateType::Dungeon, "MoveUp");
    evtMgr->removeCallback(StateType::Dungeon, "MoveRight");
    evtMgr->removeCallback(StateType::Dungeon, "MoveDown");
    evtMgr->removeCallback(StateType::Dungeon, "MoveLeft");
    
    evtMgr->removeCallback(StateType::Map, "MoveUp");
    evtMgr->removeCallback(StateType::Map, "MoveRight");
    evtMgr->removeCallback(StateType::Map, "MoveDown");
    evtMgr->removeCallback(StateType::Map, "MoveLeft");
}

void Player::update(sf::Time time){

    move(velocity * time.asSeconds());
    
    animate();
    spritesheet.update(time.asSeconds());
    
    velocity = sf::Vector2f(0.f, 0.f); // reset velocity for the next update loop
}

void Player::changeRoom(Orientation orient){

    std::string filePath = "Data/Files/Dungeon/PlayerCoordonates.cfg";
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

void Player::setBaseSpeed(float newSpeed){
    
    if(newSpeed > 0.f){
        
        baseSpeed = newSpeed;
    }
}

int Player::returnStoi(std::istringstream &ss){

    std::string result;
    std::getline(ss, result, ',');
    return std::stoi(result);
}

void Player::setVelocity(EventDetails* details){
    
    float pxMove = baseSpeed * (1.f + stats.getFinalValue(Speed)/100.f);
    
    if (details->name == "MoveUp"){
        
        velocity.y -= pxMove;
    }
    if (details->name == "MoveRight"){
        
        velocity.x += pxMove;
    }
    if (details->name == "MoveDown"){
        
        velocity.y += pxMove;
    }
    if (details->name == "MoveLeft"){
        
        velocity.x -= pxMove;
    }
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const{

    states.transform *= getTransform();
    target.draw(spritesheet, states);
}

void Player::animate(){

    if(velocity.x != 0.f || velocity.y != 0.f){

        if(velocity.y < 0.f && abs(velocity.y) > abs(velocity.x)){
            
            spritesheet.setAnimation("Moving", true, true);
            spritesheet.setOrientation(Orientation::North);
        }

        else if(velocity.x > 0.f && abs(velocity.x) >= abs(velocity.y)){
            
            spritesheet.setAnimation("Moving", true, true);
            spritesheet.setOrientation(Orientation::East);
        }

        else if(velocity.y > 0.f && abs(velocity.y) > abs(velocity.x)){
            
            spritesheet.setAnimation("Moving", true, true);
            spritesheet.setOrientation(Orientation::South);
        }

        else if(velocity.x < 0.f && abs(velocity.x) >= abs(velocity.y)){
            
            spritesheet.setAnimation("Moving", true, true);
            spritesheet.setOrientation(Orientation::West);
        }
    }
    else{
        
        spritesheet.setAnimation("Idle", false, false);
        spritesheet.setOrientation(Orientation::South);
    }
}
