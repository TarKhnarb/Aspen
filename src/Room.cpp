#include "Room.h"

/***************
 * Constructor *
 ***************/
Room::Room(TextureManager* textureMgr, Room::Type roomType):
        textureMgr(textureMgr){
            
    setType(roomType);
    
    textureMgr->requireResource("Room");
    sprite.setTexture(*textureMgr->getResource("Room"));
}

Room::~Room(){
    
    textureMgr->releaseResource("Room");
}

/***********
 * SetType *
 ***********/
void Room::setType(Room::Type roomType){

    type = roomType;
    
    if (type == Boss)
        sprite.setColor(sf::Color(80, 170, 255));
}

/***********
 * GetType *
 ***********/
Room::Type Room::getType() const{

    return type;
}

/***********
 * AddDoor *
 ***********/
void Room::addDoor(Orientation orient, DoorState state){

    if(doors.find(orient) != doors.end()) // We show if the door already exist
        setDoorState(orient, state);
    else // else create it
        doors.emplace(orient, state);
}

/****************
 * SetDoorState *
 ****************/
void Room::setDoorState(Orientation orient, DoorState state){ // Set state of a door according orientation

    auto found = doors.find(orient);

    if(found != doors.end()) // find the right door
        found->second = state;
    else // else add it
        throw std::out_of_range("Room::setDoorState() : cette porte n'existe pas " + static_cast<int>(orient));
}

/************
 * GetDoors *
 ************/
std::map<Orientation, DoorState> Room::getDoors() const{

    return doors;
}

/***********
 * GetDoor *
 ***********/
DoorState Room::getDoorState(Orientation orient) const{

    auto found = doors.find(orient);

    if(found != doors.end())
        return found->second;
    else
        throw std::out_of_range("Room::getDoorState() : cette porte n'existe pas " + std::to_string(static_cast<int>(orient)));
}

/*************
 * OpenDoors *
 *************/
void Room::openDoors(){

    for(auto &d : doors){

        if(d.second != DoorState::Key)
            d.second = DoorState::Open;
    }
}

/*************
 * CloseDoors *
 *************/
void Room::closeDoors(){

    for(auto &d : doors){

        if(d.second != DoorState::Key)
            d.second = DoorState::Closed;
    }
}

/**************
 * AffectType *
 **************/
void Room::affectType(unsigned seed){

    bool north = (doors.find(Orientation::North) != doors.end());
    bool east = (doors.find(Orientation::East) != doors.end());
    bool south = (doors.find(Orientation::South) != doors.end());
    bool west = (doors.find(Orientation::West) != doors.end());

    switch(doors.size()){

        case 1:

            if(north)
                setType(Type::N);
            else if(east)
                setType(Type::E);
            else if(south)
                setType(Type::S);
            else if(west)
                setType(Type::W);

            break;

        case 2:

            if(north && south){

                if((rand()%seed)%2)
                    setType(Type::NS1);
                else
                    setType(Type::NS2);
            }
            else if(east && west){

                if((rand()%seed)%2)
                    setType(Type::WE1);
                else
                    setType(Type::WE2);
            }
            else if(north && east){
                setType(Type::NE);
            }
            else if(east && south){
                setType(Type::ES);
            }
            else if(south && west){
                setType(Type::SW);
            }
            else if(west && north){
                setType(Type::NW);
            }
            break;


        case 3:

            if(!west)
                setType(Type::NES);
            else if(!north)
                setType(Type::ESW);
            else if(!east)
                setType(Type::NSW);
            else if(!south)
                setType(Type::NEW);
            break;

        case 4:

            if((rand()%seed)%2)
                setType(Type::NESW1);
            else
                setType(Type::NESW2);
            break;

        default:
            break;
    }
}

/*****************
 * MakeRoomTiles *
 *****************/
void Room::makeRoomTiles(){

    std::ifstream file;
    std::string filename(takeTilesPath(static_cast<int>(type)));
    file.open(filename);
    
    std::string previousLine; // use to read the tile above
    std::string line;
    if(file.is_open()){
        
        std::size_t lineNb = 0;
        while(!file.eof()){

            getline(file, line);
            for(std::size_t i = 0; i < line.size(); ++i){
                switch(std::stoi(line.substr(i, 1))){
                    
                    case 1: // hole
                        {
                            bool border = (lineNb == 0 || std::stoi(previousLine.substr(i, 1)) != 1);
                            std::unique_ptr<Hole> hole (new Hole(border, textureMgr));
                            hole->setPosition(205.f + 30.f * i, 135.f + 30.f * lineNb);
                            entities.push_back(std::move(hole));
                        }
                        break;
                    
                    case 2: // rock
                        {
                            std::unique_ptr<Rock> rock (new Rock(10, textureMgr));
                            rock->setPosition(205.f + 30.f * i, 135.f + 30.f * lineNb);
                            entities.push_back(std::move(rock));
                        }
                        break;
                    
                    case 3: // chest
                        break;
                    
                    case 4: // boost
                        break;
                    
                    default:
                        break;
                }
            }
            
            previousLine = line;
            ++lineNb;
        }

    }
    else
        throw std::runtime_error ("Failed to load " + filename);

    file.close();
}

/*****************
 * TakeTilesPath *
 *****************/
std::string Room::takeTilesPath(int roomId){
    
    std::string path;
    
    std::ifstream file;
    std::string filename("Data/Files/Dungeon/Rooms/All.cfg");
    file.open(filename);

    if(file.is_open()) {

        for(int i = 0; i != roomId; ++i){

            if(file.eof())
                throw std::runtime_error("Failed to load id " + std::to_string(roomId));

            getline(file, path);
        }

    }
    else
        throw std::runtime_error ("Failed to load " + filename);

    file.close();

    return path;
}

/********
 * draw *
 ********/

void Room::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    
    target.draw(sprite, states);
    for (const auto& entity : entities){
        
        target.draw(*entity, states);
    }
}
