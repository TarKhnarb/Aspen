#include "Room.h"

/***************
 * Constructor *
 ***************/
Room::Room(Room::Type roomType):
        type(roomType){}

/***********
 * SetType *
 ***********/
void Room::setType(Room::Type roomType){

    type = roomType;
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
            else{
                setType(NESW2);
            }
            break;


        case 3:

            if((rand()%seed)%4){

                if(!west)
                    setType(Type::NES);
                else if(!north)
                    setType(Type::ESW);
                else if(!east)
                    setType(Type::NSW);
                else if(!south)
                    setType(Type::NEW);
            }
            else{
                setType(Type::NESW2);
            }
            break;

        case 4:

            if((rand()%seed)%3)
                setType(Type::NESW1);
            else
                setType(Type::NESW2);
            break;

        default:
            break;
    }

    makeRoomTiles();
}

std::vector<std::vector<unsigned>> Room::getRoomTiles() const{

    return roomTiles;
}

/***********
 * Display *
 ***********/
void Room::display(){ // TODO a virer une fois tout les tests réalisés

    std::cout << "Type de salle : " << type << std:: endl;
    std::cout << std::endl;
    std::cout << "Doors :" << std::endl;

    for(auto &d : doors){
        std::cout << "      Orientation : " << static_cast<int>(d.first) << std::endl;
        std::cout << "      State : " << static_cast<int>(d.second) << std::endl;
        std::cout << std::endl;
    }
}

/*****************
 * MakeRoomTiles *
 *****************/
void Room::makeRoomTiles(){

    std::ifstream file;
    std::string filename(takeTilesPath(static_cast<int>(type)));
    file.open(filename);

    std::string line;
    if(file.is_open()){

        while(!file.eof){

            getline(file, line);
            for(std::size_t i = 0; i < line.size(); ++i)
                roomTiles.back().push_back(std::stou(line.substr(i, 1)));
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

    std::ifstream file;
    std::string filename("Data/Files/Dungeon/Rooms/All.cfg");
    file.open(filename);

    if(file.is_open()) {

        std::string path;
        for(unsigned i = 1; i != roomId; ++i){

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

void Room::fillRoomUnit(){

    for(auto &d : )
}