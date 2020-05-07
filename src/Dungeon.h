#ifndef DUNGEON_GAME_H
#define DUNGEON_GAME_H

#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <stdexcept>

#include "Stage.h"

class Dungeon{

public:

    Dungeon(); // Lit les information necessaire et les stock dans Informations

public: /** Functions */

    void nextStage();

    Room* getRoom(unsigned i, unsigned j) const;

private: /** Functions */

    void fillInformation();

    unsigned returnCsvItemSTOI(std::istringstream &ss);

    void setStage();

private: /** Variables */

    unsigned maxStageNumber; // ( = informations.size() )

    unsigned actualStage;

    std::vector<std::vector<unsigned>> information; // each information to generate a stage according its level
    /*
     * vector<unsigned> stage size (odd), minStageRoom, maxStageRoom
     */

    std::unique_ptr<Stage> currentStage;

    std::string filePath;
};

#endif