#ifndef DUNGEON_GAME_H
#define DUNGEON_GAME_H

#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <stdexcept>

#include "Stage.h"
#include "Orientation.h"

class Dungeon{

public:

    Dungeon(TextureManager*); // Lit les information necessaire et les stock dans Informations

public:

    void nextStage();

    Room* getRoom(unsigned i, unsigned j) const; // TODO change for minimap

    Room* changeRoom(Orientation orient); // TODO change posDungeon value
    // TODO make getCurrentRoom

    unsigned getDungeonSize();

    void setPosDungeon(unsigned i, unsigned j);

    std::pair<int,int> getPosDungeon() const;

private:

    void fillInformation();

    unsigned returnCsvItemSTOI(std::istringstream &ss);

    void setStage();

private:

    unsigned maxStageNumber; // ( = informations.size() )

    unsigned actualStage;

    std::vector<std::vector<unsigned>> information; // each information to generate a stage according its level
    /*
     * vector<unsigned> stage size (odd), minStageRoom, maxStageRoom
     */

    std::unique_ptr<Stage> currentStage;

    std::pair<unsigned, unsigned> posDungeon; // TODO changes with sf::Vector2u

    std::string filePath;
    
    TextureManager* textureMgr;
};

#endif
