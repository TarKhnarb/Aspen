#ifndef GAME_ROOM_H
#define GAME_ROOM_H

#include <SFML/System/Vector2.hpp>
#include <map>
#include <utility>
#include <cassert>

#include "Orientation.h"

class Room{

public:

    enum RoomType{

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

    enum State{

        Open,
        Close,
        Key
    };

    Room(RoomType roomType);

public: // Functions

    void setType(RoomType roomType = RoomType::Common);

    Room::RoomType getType() const;

    void addDoor(Orientation orient, State state);

    void setDoorState(Orientation orient, State state); // Set state of a door according orientation return true if the doors have be find

    std::map<Orientation, Room::State> getDoors() const;

    std::pair<Orientation, Room::State> getDoor(Orientation orient) const;

private: // Variables

    std::map<Orientation, State> doors;

    RoomType type;
};

#endif