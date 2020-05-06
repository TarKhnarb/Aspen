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

void Room::openDoors(){

    for(auto &d : doors){

        if(d.second != DoorState::Key)
            d.second = DoorState::Open;
    }
}

void Room::closeDoors(){

    for(auto &d : doors){

        if(d.second != DoorState::Key)
            d.second = DoorState::Close;
    }
}