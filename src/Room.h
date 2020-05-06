#ifndef GAME_ROOM_H
#define GAME_ROOM_H

#include <SFML/System/Vector2.hpp>
#include <map>
#include <utility>
#include <cassert>
#include <stdexcept>

#include "Orientation.h"

enum class DoorState{

    Open,
    Close,
    Key
};

class Room{

public:

    enum Type{

        Common,
        Start,
        Boss,
        Room2NS1,
        Room2NS2,
        Room2WE1,
        Room2WE2,
        Room4NESW1,
        Room4NESW2,
        Room1N,
        Room1E,
        Room1W,
        Room3NES,
        Room3ESW,
        Room3NSW,
        Room3NEW
    };

public:

    Room(const Room&) = delete;

    Room(Type roomType = Type::Common);

public: // Functions

    void setType(Type roomType);

    Type getType() const;

    void addDoor(Orientation orient, DoorState state = DoorState::Open);

    void setDoorState(Orientation orient, DoorState state); // Set state of a door according orientation return true if the doors have be find

    DoorState getDoorState(Orientation orient) const;

    void openDoors();

    void closeDoors();

private: // Variables

    std::map<Orientation, DoorState> doors;

    Type type;
};

#endif