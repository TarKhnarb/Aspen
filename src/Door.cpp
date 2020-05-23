#include "Door.h"

/***************
 * Constructor *
 ***************/
Door::Door(Orientation orient, State dState, TextureManager *textureMgr, sf::Color color):
        Entity(textureMgr, Type::Door),
        orientation(orient),
        state(dState){

    textureName = (state == State::Open) ? "OpenDoor" : "ClosedDoor";

    textureMgr->requireResource(textureName);
    spriteDoor.setTexture(*textureMgr->getResource(textureName));
    
    sf::FloatRect rectDoor = spriteDoor.getLocalBounds();
    collisionBox = rectDoor;
    setOrigin(rectDoor.width/2.f, rectDoor.height/2.f);

    textureMgr->requireResource("Frame");
    spriteFrame.setTexture(*textureMgr->getResource("Frame"));
    spriteFrame.setColor(color);

    placeDoor();
}

/**************
 * Destructor *
 **************/
Door::~Door(){

        textureMgr->releaseResource(textureName);
        textureMgr->releaseResource("Frame");
}

/************
 * GetState *
 ************/
Door::State Door::getState() const{

    return state;
}

/************
 * SetState *
 ************/
void Door::setState(State state){

    textureMgr->releaseResource(textureName);
    this->state = state;

    textureName = this->state == State::Open ? "OpenDoor" : "ClosedDoor";

    textureMgr->requireResource(textureName);
    spriteDoor.setTexture(*textureMgr->getResource(textureName));
    
    placeDoor();
}

/******************
 * GetOrientation *
 ******************/
Orientation Door::getOrientation() const{

    return orientation;
}

/*************
 * PlaceDoor *
 *************/
void Door::placeDoor(){

    std::string filePath = "Data/Files/Dungeon/DoorCoordinates.cfg";
    std::ifstream file;
    file.open(filePath);

    float x, y;

    if(file.is_open()){

        std::string csvItem;
        for(unsigned i = 0; i <= static_cast<unsigned>(orientation); ++i){

            getline(file, csvItem);
        }
        std::istringstream iss(csvItem);
        x = static_cast<float>(returnStoi(iss));
        y = static_cast<float>(returnStoi(iss));
    }
    else
        throw std::runtime_error ("Failed to load " + filePath);

    file.close();

    setPosition(x, y);

    switch(orientation){

        case Orientation::North:
            collisionBox.left = x - 135.f/2.f;
            collisionBox.top = y - 45.f;
            collisionBox.width = 135.f;
            collisionBox.height = 90.f;

            break;

        case Orientation::East:
            setRotation(90.f);
            collisionBox.left = x - 45.f;
            collisionBox.top = y - 135.f/2.f;
            collisionBox.width = 90.f;
            collisionBox.height = 135.f;

            break;

        case Orientation::South:
            setRotation(180.f);
            collisionBox.left = x - 135.f/2.f;
            collisionBox.top = y - 45.f;
            collisionBox.width = 135.f;
            collisionBox.height = 90.f;
            break;

        case Orientation::West:
            setRotation(-90.f);
            collisionBox.left = x - 45.f;
            collisionBox.top = y - 135.f/2.f;
            collisionBox.width = 90.f;
            collisionBox.height = 135.f;
            break;

        default: // TODO clean all of this after Entity::setRotation
            break;
    }
}

/*********************
 * ReturnCsvItemSTOI *
 *********************/
unsigned Door::returnStoi(std::istringstream &ss){

    std::string result;
    std::getline(ss, result, ',');
    return std::stoi(result);
}

/********
 * Draw *
 ********/
void Door::draw(sf::RenderTarget &target, sf::RenderStates states) const{

    states.transform *= getTransform();
    target.draw(spriteDoor, states);
    target.draw(spriteFrame, states);
}