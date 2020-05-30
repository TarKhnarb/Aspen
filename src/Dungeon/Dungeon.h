#ifndef DUNGEON_GAME_H
#define DUNGEON_GAME_H

#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <stdexcept>
#include <SFML/System/Vector2.hpp>

#include "Stage.h"
#include "../Orientation.h"

class Dungeon{

public:

    Dungeon() = delete;
    Dungeon(SharedContext*); // Lit les information necessaire et les stock dans Informations

public:

    void nextStage();

    Room::Type getRoomType(unsigned i, unsigned j) const;

    Room* getCurrentRoom() const;
    
    void changeRoom(Orientation orient);

    unsigned getDungeonSize() const;

    void setPosDungeon(unsigned i, unsigned j);

    sf::Vector2u getPosDungeon() const;

    bool end() const;

private:

    void fillInformation();

    unsigned returnCsvItemSTOI(std::istringstream &ss);

    void setStage(); // TODO complete with seed managment

private:

    unsigned maxStageNumber; // ( = informations.size() )

    unsigned actualStage;

    std::vector<std::vector<unsigned>> information; // each information to generate a stage according its level
    /*
     * vector<unsigned> stage size (odd), minStageRoom, maxStageRoom
     */

    std::unique_ptr<Stage> currentStage;

    sf::Vector2u posDungeon;

    std::string filePath;
    
    SharedContext *context;
};

#endif
