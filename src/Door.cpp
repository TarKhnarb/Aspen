#include "Door.h"

/***************
 * Constructor *
 ***************/
Door::Door(Orientation orient, State dState, TextureManager *textureMgr):
        orientation(orient),
        state(dState),
        Entity(textureMgr, Type::Door){

    textureName = state == State::Open ? "OpenDoor" : "ClosedDoor";

    textureMgr->requireResource(textureName);
    spriteDoor.setTexture(*textureMgr->getResource(textureName));
    sf::FloatRect rectDoor = spriteDoor.getLocalBounds();
    spriteDoor.setOrigin(rectDoor.width/2.f, rectDoor.height/2.f);
    collisionBox = rectDoor;

    textureMgr->requireResource("Frame");
    spriteFrame.setTexture(*textureMgr->getResource("Frame"));
    spriteFrame.setOrigin(spriteFrame.getLocalBounds().width/2.f, spriteFrame.getLocalBounds().height/2.f);

    placeDoor();
}

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
void Door::setState(State dState){

    textureMgr->releaseResource(textureName);
    state = dState;

    textureName = state == State::Open ? "OpenDoor" : "ClosedDoor";

    textureMgr->requireResource(textureName);
    spriteDoor.setTexture(*textureMgr->getResource(textureName));
    sf::FloatRect rectDoor = spriteDoor.getLocalBounds();
    spriteDoor.setOrigin(rectDoor.width/2.f, rectDoor.height/2.f);
    collisionBox = rectDoor;
    placeDoor();
}

/******************
 * GetOrientation *
 ******************/
Orientation Door::getOrientation() const{

    return orientation;
}

/********
 * Draw *
 ********/
void Door::draw(sf::RenderTarget &target, sf::RenderStates states) const{

    states.transform *= getTransform();
    target.draw(spriteDoor, states);
    target.draw(spriteFrame, states);
}

/*************
 * PlaceDoor *
 *************/
void Door::placeDoor(){

    std::string filePath = "Data/Files/Dungeon/DoorCoordonates.cfg";
    std::ifstream file;
    file.open(filePath);

    float x, y;

    if(file.is_open()){

        std::string csvItem;
        for(unsigned i = 0; i <= static_cast<unsigned>(orientation); ++i){

            getline(file, csvItem);
        }
        std::istringstream iss(csvItem);
        x = static_cast<float>(returnCsvItemSTOF(iss));
        y = static_cast<float>(returnCsvItemSTOF(iss));
    }
    else
        throw std::runtime_error ("Failed to load " + filePath);

    file.close();

    spriteFrame.setPosition(x, y);
    spriteDoor.setPosition(x, y);

    switch(orientation){
        case Orientation::East:
            spriteFrame.setRotation(90.f);
            spriteDoor.setRotation(90.f);
            break;

        case Orientation::South:
            spriteFrame.setRotation(180.f);
            spriteDoor.setRotation(180.f);
            break;

        case Orientation::West:
            spriteFrame.setRotation(-90.f);
            spriteDoor.setRotation(-90.f);
            break;

        default:
            break;
    }
}

/*********************
 * ReturnCsvItemSTOI *
 *********************/
unsigned Door::returnCsvItemSTOF(std::istringstream &ss){
    std::string result;
    std::getline(ss, result, ',');
    return std::stoi(result);
}