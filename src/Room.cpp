#include "Room.h"

/***************
 * Constructor *
 ***************/
Room::Room(TextureManager *textureMgr, Room::Type roomType):
        color(sf::Color::White),
        textureMgr(textureMgr){
            
    setType(roomType);
    
    textureMgr->requireResource("Room");
    background.setTexture(*textureMgr->getResource("Room"));

    placeWalls();
}

/**************
 * Destructor *
 **************/
Room::~Room(){
    
    textureMgr->releaseResource("Room");
}

/***********
 * SetType *
 ***********/
void Room::setType(Room::Type roomType){

    type = roomType;
    
    switch(type){ // colorize the room
        
        case Boss:
            {
                color = sf::Color(80, 170, 255);
                
                std::unique_ptr<Hatch> hatch(new Hatch(textureMgr, color)); // add a trapdoor to the room
                hatchs.push_back(std::move(hatch));
            }
            break;
        
        case Start:
        case CommonStart:
            color = sf::Color(255, 244, 66);
            break;
            
        case Boost:
            color = sf::Color(80, 255, 220);
            break;
        
        default:
            break;
    }
    
    background.setColor(color);
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

    auto hasOrient = [orient] (const auto& door) { return door->getOrientation() == orient; };
    auto found = std::find_if(doors.begin(), doors.end(), hasOrient);

    if(found == doors.end()) // We show if the door don't already existing
        doors.emplace_back(new Door(orient, state, textureMgr, color));

    else
        throw std::invalid_argument("Room::addDoor() : the door already exist with this Orientation: " + std::to_string(static_cast<int>(orient)));
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
            else if(north && east)
                setType(Type::NE);
            else if(east && south)
                setType(Type::ES);
            else if(south && west)
                setType(Type::SW);
            else if(west && north)
                setType(Type::NW);
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

/**************
 * PlaceTiles *
 **************/
void Room::placeTiles(){

    std::ifstream file;
    std::string filename(getTilesPath(static_cast<int>(type)));
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
                            std::unique_ptr<Hole> hole (new Hole(border, textureMgr, color));
                            hole->setPosition(205.f + 30.f * i, 135.f + 30.f * lineNb);
                            holes.push_back(std::move(hole));
                        }
                        break;
                    
                    case 2: // rock
                        {
                            std::unique_ptr<Rock> rock (new Rock(10, textureMgr));
                            rock->setPosition(205.f + 30.f * i, 135.f + 30.f * lineNb);
                            rocks.push_back(std::move(rock));
                        }
                        break;
                    
                    case 3: // chest
                        {
                            std::unique_ptr<Chest> chest(new Chest(textureMgr, Chest::Closed));
                            chest->setPosition(205.f + 30.f * i, 135.f + 30.f * lineNb);
                            chests.push_back(std::move(chest));
                        }
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

/***********************
 * CheckRoomCollisions *
 ***********************/
std::pair<Entity::Type, Orientation> Room::checkRoomCollisions(Character& entity){
    
    for(const auto &door : doors){
        
        if(entity.collides(*door, 0.f) && entity.getType() == Entity::Player){

            return std::make_pair(Entity::Door, door->getOrientation());
        }
    }
    
    for(const auto &wall : walls){
        
    entity.collides(*wall, 0.f);
    }
    
    if(!entity.getStats()->getFinalValue(CanFly)){
        
        for(const auto &hole : holes){
            
            entity.collides(*hole, 0.f);
        }
        
        for(const auto &rock : rocks){
            
            entity.collides(*rock, 0.f);
        }
    }
    
    for(const auto &chest : chests){
        
        if(entity.collides(*chest, 0.f) && entity.getType() == Entity::Player){
            
            return std::make_pair(Entity::Chest, static_cast<Orientation>(0));
        }
    }

    for(const auto &hatch : hatchs){

        if(entity.collides(*hatch, 0.f) && entity.getType() == Entity::Player){
            
            return std::make_pair(Entity::Hatch, static_cast<Orientation>(0));
        }
    }
    
    return std::make_pair(Entity::None, static_cast<Orientation>(0));
}

/**************************
 * CheckMonsterCollisions *
 **************************/
void Room::checkMonsterCollisions(Character& entity){}

/*****************************
 * CheckProjectileCollisions *
 *****************************/
void Room::checkProjectileCollisions(Character& entity){

    for(const auto &proj : projectiles){
        
        if(proj->collides(entity, 0.f)){
            
            //toRemove.push_back(??);
            //entity.hit(proj.damages)
        }
    }
}

void Room::checkProjRoomCollisions(){
    
    std::size_t projNb = 0;
    
    for(const auto &proj : projectiles){
        
        for(const auto &wall : walls){
            
            if(proj->collides(*wall, 0.f)){
                
                toRemove.push_back(projNb);
            }
        }
        
        for(const auto &rock : rocks){
            
            if(proj->collides(*rock, 0.f)){
                
                toRemove.push_back(projNb);
                rock->hit(1);
            }
        }
        
        for(const auto &chest : chests){
            
            if(proj->collides(*chest, 0.f)){
                
                toRemove.push_back(projNb);
            }
        }
        
        ++projNb;
    }
}

void Room::processRequests(){
    
    while(toRemove.begin() != toRemove.end()){
        
        std::size_t index = *toRemove.begin();
        std::cout << index << std::endl;
        projectiles.erase(projectiles.begin() + index);
        toRemove.erase(toRemove.begin());
        
        for(std::size_t &i : toRemove){
            
            if(index < i){
                
                --i;
            }
        }
    }
}
        

/**********
 * Update *
 **********/
void Room::update(sf::Time time){

    for(auto &proj : projectiles){

        if(proj){
            proj->update(time);
        }
    }
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

/*****************
 * AddProjectile *
 *****************/
void Room::addProjectile(Projectile *proj){

    projectiles.emplace_back(proj);
}

void Room::deleteProjectiles(){

    projectiles.resize(0);
    toRemove.resize(0);
}

/****************
 * GetTilesPath *
 ****************/
std::string Room::getTilesPath(int roomId){
    
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

/**************
 * PlaceWalls *
 **************/
void Room::placeWalls(){

    std::string filePath = "Data/Files/Dungeon/WallCoordinates.cfg";
    std::ifstream file;
    file.open(filePath);

    float x, y, Dx, Dy;

    if(file.is_open()){

        std::string csvItem;
        while(!file.eof()) {

            std::getline(file, csvItem);
            std::istringstream iss(csvItem);

            x = static_cast<float>(returnStoi(iss));
            y = static_cast<float>(returnStoi(iss));
            Dx = static_cast<float>(returnStoi(iss));
            Dy = static_cast<float>(returnStoi(iss));

            std::unique_ptr<Wall> wall(new Wall(x, y, Dx, Dy));
            walls.push_back(std::move(wall));
        }
    }
    else
        throw std::runtime_error ("Failed to load " + filePath);

    file.close();
}

/**************
 * ReturnStoi *
 **************/
int Room::returnStoi(std::istringstream &ss){

    std::string result;
    std::getline(ss, result, ',');
    return std::stoi(result);
}

/********
 * Draw *
 ********/
void Room::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    
    target.draw(background, states);
    
    for(const auto &door : doors){
        
        target.draw(*door, states);
    }
    
    for(const auto &hole : holes){
        
        target.draw(*hole, states);
    }
    
    for(const auto &rock : rocks){
        
        target.draw(*rock, states);
    }
    
    for(const auto &chest : chests){
        
        target.draw(*chest, states);
    }

    for(const auto &hatch : hatchs){

        target.draw(*hatch, states);
    }

    for(const auto &proj : projectiles){

        if(proj){
            target.draw(*proj, states);
        }
    }
}
