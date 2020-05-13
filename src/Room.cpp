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
        sprite.setColor(sf::Color(20, 20, 255, 128));
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
void Room::addDoor(const Orientation &orient, const Door::State &state){

    auto found = std::find_if(doors.begin(), doors.end(), [orient] (const auto& d) { return d->getOrientation() == orient; });

    if(found == doors.end()) // We show if the door don't already existing
        doors.emplace_back(new Door(orient, state, textureMgr));
    else
        throw std::invalid_argument("Room::addDoor() : the door already exist with this Orientation: " + std::to_string(static_cast<int>(orient)));
}

/*************
 * OpenDoors *
 *************/
void Room::openDoors(){

    for(auto &d : doors){

        if(d->getState() != Door::State::Key)
            d->setState(Door::State::Open);
    }
}

/*************
 * CloseDoors *
 *************/
void Room::closeDoors(){

    for(auto &d : doors){

        if(d->getState() != Door::State::Key)
            d->setState(Door::State::Closed);
    }
}

/**************
 * AffectType *
 **************/
void Room::affectType(unsigned seed){

    bool north = false;
    bool east = false;
    bool south = false;
    bool west = false;
    for(auto &d : doors){

        Orientation orient = d->getOrientation();
        if(orient == Orientation::North)
            north = true;
        if(orient == Orientation::East)
            east = true;
        if(orient == Orientation::South)
            south = true;
        if(orient == Orientation::West)
            west = true;
    }

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

void Room::makeRoomDoor(){

    for(auto &d : doors){


        entities.push_back(std::move(d));
    }
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
 * Draw *
 ********/
void Room::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    
    target.draw(sprite, states);
    for (const auto& entity : entities){
        
        target.draw(*entity, states);
    }
}
