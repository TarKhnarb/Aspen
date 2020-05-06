#ifndef GAME_STAGE_H
#define GAME_STAGE_H

#include <memory>

#include "Room.h"
#include "Orientation.h"

class Stage{

public:

    Stage(const Stage&) = delete;

    Stage(unsigned size, unsigned minRoom, unsigned maxRoom);

    ~Stage();

public: /** Functions */

    void generate(unsigned &stageNumber, unsigned seed = 1);

private: /** Functions */

    void setSeed();

    void reset(unsigned stage);

    bool checkRoomAround(unsigned i, unsigned j);

    void placeDoors();

private: /** Variables */

    unsigned stageSize;

    std::vector<std::vector<std::unique_ptr<Room>>> roomMap;

    bool needGenerate;

    unsigned stageSeed;

    unsigned minRoomSize;

    unsigned maxRoomSize;
};

#endif