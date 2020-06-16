#ifndef GAME_ROOM_H
#define GAME_ROOM_H

#include <SFML/Graphics/Color.hpp>

#include <map>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <functional>

#include "../SharedContext.h"
#include "../Entity/RoomElements/Rock.h"
#include "../Entity/RoomElements/Hole.h"
#include "../Entity/RoomElements/Chest.h"
#include "../Entity/RoomElements/Wall.h"
#include "Door.h"
#include "../Entity/RoomElements/Hatch.h"
#include "../Entity/RoomElements/Projectile.h"
#include "../Entity/Monster/Virus.h"

class Room : public sf::Drawable{

public:

    enum Type{

        Common = 0,
        Start,
        CommonStart,
        Boss,
        Boost,
        N,
        E,
        S,
        W,
        NS1,
        NS2,
        WE1,
        WE2,
        NE,
        ES,
        SW,
        NW,
        NES,
        ESW,
        NSW,
        NEW,
        NESW1,
        NESW2,
        None
    };

    enum class Tile{

        Nothing = 0,
        Hole,
        Rock,
        Chest,
        Boost
    };

public:

    Room() = delete;
    Room(SharedContext*, Type roomType = Type::Common);
    ~Room();

public: // Functions
    
    void setType(Type roomType);

    Type getType() const;

    void addDoor(const Orientation &orient, const Door::State &state = Door::State::Closed);

    void affectType(unsigned seed);
    
    void placeTiles();
    
    void update(sf::Time);
    
    std::pair<Entity::Type, Orientation> checkRoomCollisions(Character&);
    
    void checkMonsterCollisions(Character&);

    void checkProjectileCollisions(Character&);
    
    void processRequests();
    
    void openDoors();

    void closeDoors();

    void addProjectile(Projectile *proj);

    void deleteProjectiles();

private:

    std::string getTilesPath(int roomId); // return Room path witch type corresponding

    void placeWalls();
    
    void checkProjRoomCollisions();
    
    void checkProjMonstersCollisions();

    void draw(sf::RenderTarget&, sf::RenderStates) const override;
    
    int returnStoi(std::istringstream &ss);
    
private: // Variables
    
    sf::Sprite background;
    sf::Color color;
    
    std::vector<std::unique_ptr<Door>> doors;
    std::vector<std::unique_ptr<Wall>> walls;
    std::vector<std::unique_ptr<Hole>> holes;
    std::vector<std::unique_ptr<Rock>> rocks;
    std::vector<std::unique_ptr<Chest>> chests;
    std::vector<std::unique_ptr<Hatch>> hatchs;
    std::vector<std::unique_ptr<Projectile>> projectiles;
    std::vector<std::unique_ptr<Monster>> monsters;
    
    std::vector<std::size_t> toRemove;

    Type type;
    
    SharedContext *context;
    TextureManager *textureMgr;
};

#endif
