#ifndef GAME_ROOM_H
#define GAME_ROOM_H

#include <map>
#include <utility>
#include <cassert>
#include <stdexcept>
#include <iostream>

#include "Orientation.h"

enum class DoorState{

    Open,
    Closed,
    Key
};

class Room{

public:

    enum Type{

        Common,
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

public:

    Room(const Room&) = delete;

    Room(Type roomType = Type::Common);

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

    void display(); // TODO a virer une fois tout les tests réalisés

private: // Variables

    std::map<Orientation, DoorState> doors;

    Type type;
};

#endif