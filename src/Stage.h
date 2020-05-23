#ifndef GAME_STAGE_H
#define GAME_STAGE_H

#include <iostream>
#include <memory>
#include <vector>
#include <map>

#include "Room.h"
#include "Orientation.h"

class Stage{

public:

    Stage() = delete;

    Stage(unsigned size, unsigned minRoom, unsigned maxRoom, TextureManager*);

public:

    void generate(unsigned &stageNumber, unsigned seed = 1);

    Room* getRoom(unsigned i, unsigned j) const;

    unsigned getSize() const;

private:

    void setSeed(unsigned seed);

    void reset(unsigned stage);

    bool checkRoomAround(unsigned i, unsigned j, Room::Type type = Room::Common);

    void placeDoors();

    void affectRoomsType(); // affects types and fills rooms

private:

    unsigned stageSize;

    std::vector<std::vector<std::unique_ptr<Room>>> roomMap;

    unsigned stageSeed;

    unsigned minRoomCount;

    unsigned maxRoomCount;
    
    TextureManager* textureMgr;
};

std::ostream& operator<<(std::ostream& stream, Stage &s);

#endif
