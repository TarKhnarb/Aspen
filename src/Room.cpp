#include "Room.h"

/***************
 * Constructor *
 ***************/
Room::Room(RoomType roomType):
        type(roomType){}

/***********
 * SetType *
 ***********/
void Room::setType(RoomType roomType){

    type = roomType;
}

/***********
 * GetType *
 ***********/
Room::RoomType Room::getType() const{

    return type;
}

/***********
 * AddDoor *
 ***********/
void Room::addDoor(Orientation orient, State state){

    if(doors.find(orient) != doors.end()) // We show if the door already exist
        setDoorState(orient, state);
    else // else create it
        doors.emplace(orient, state);
}

/****************
 * SetDoorState *
 ****************/
void Room::setDoorState(Orientation orient, State state) {// Set state of a door according orientation

    if(doors.find(orient) != doors.end()) // find the right door
        doors.find(orient)->second = state;
    else // else add it
        doors.emplace(orient, state);
}

/************
 * GetDoors *
 ************/
std::map<Orientation, Room::State> Room::getDoors() const{

    return doors;
}

/***********
 * GetDoor *
 ***********/
std::pair<Orientation, Room::State> Room::getDoor(Orientation orient) const{

    assert(doors.find(orient) != doors.end());

    auto find = doors.find(orient);

    return std::make_pair(find->first, find->second);
}