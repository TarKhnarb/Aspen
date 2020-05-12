#ifndef GAME_ROOM_H
#define GAME_ROOM_H

#include <map>
#include <vector>
#include <utility>
#include <cassert>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <sstream>

#include "Orientation.h"
#include "Rock.h"

enum class DoorState{

    Open,
    Closed,
    Key
};

class Room{

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
        NES,
        ESW,
        NSW,
        NEW,
        NESW1,
        NESW2
    };

    enum class Tile{

        Nothing = 0,
        Hole,
        Rock,
        Chest,
        Boost
    };

public:

    Room(const Room&) = delete;

    Room(TextureManager*, Type roomType = Type::Common);

public: // Functions

    void setType(Type roomType);

    Type getType() const;

    void addDoor(Orientation orient, DoorState state = DoorState::Closed);

    void setDoorState(Orientation orient, DoorState state); // Set state of a door according orientation return true if the doors have be find

    std::map<Orientation, DoorState> getDoors() const;

    DoorState getDoorState(Orientation orient) const;

    void openDoors();

    void closeDoors();

    void affectType(unsigned seed);

    std::vector<std::vector<unsigned>> getRoomTiles() const;

private:

    void makeRoomTiles(); // TODO create entities depending on the file

    std::string takeTilesPath(unsigned roomId); // return Room path witch type corresponding

private: // Variables

    std::map<Orientation, DoorState> doors;

    Type type;

    std::vector<std::vector<unsigned>> roomTiles; // TODO delete this

    TextureManager* textureMgr;
};

#endif
