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

    Stage(const Stage&) = delete;

    Stage(unsigned size, unsigned minRoom, unsigned maxRoom);

public: /** Functions */

    void generate(unsigned &stageNumber, unsigned seed = 1);

    Room* getRoom(unsigned i, unsigned j) const;

    unsigned getSize() const;

private: /** Functions */

    void setSeed(unsigned seed);

    void reset(unsigned stage);

    bool checkRoomAround(unsigned i, unsigned j);

    void placeDoors();

    /*
     * créer une fonction qui retourne un map map<Orientation, Room::Type>
     */

private: /** Variables */

    unsigned stageSize;

    std::vector<std::vector<std::unique_ptr<Room>>> roomMap;

    unsigned stageSeed;

    unsigned minRoomCount;

    unsigned maxRoomCount;
};

std::ostream& operator<<(std::ostream& stream, const Stage &s);

#endif