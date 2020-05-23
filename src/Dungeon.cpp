#include "Dungeon.h"

/***************
 * Constructor *
 ***************/
Dungeon::Dungeon(TextureManager* textureMgr):
        actualStage(0),
        filePath("Data/Files/Dungeon/DungeonInformations.csv"),
        textureMgr(textureMgr){

    fillInformation();
    maxStageNumber = information.size();

    setStage();
}

/*************
 * NextStage *
 *************/
void Dungeon::nextStage(){

    if(actualStage < maxStageNumber)
        setStage();
}

/***********
 * GetRoom *
 ***********/
Room::Type Dungeon::getRoomType(unsigned i, unsigned j) const{

    if(currentStage){
        
        Room* room = currentStage->getRoom(i, j);
        
        if (room){
            
            return room->getType();
        }
        else{
            
            return Room::None;
        }
    }
    else{
        throw std::runtime_error("Dungon::getRoomType() : Unaccessible stage");
    }
}

Room* Dungeon::getCurrentRoom() const{
    
    return currentStage->getRoom(posDungeon.x, posDungeon.y);
}

/**************
 * ChangeRoom *
 **************/
void Dungeon::changeRoom(Orientation orient){

    getCurrentRoom()->deleteProjectiles();

    switch(orient){
        case Orientation::North:
            if (getRoomType(posDungeon.x - 1, posDungeon.y) != Room::None){
                posDungeon.x -= 1;
            }
            break;

        case Orientation::East:
            if (getRoomType(posDungeon.x, posDungeon.y + 1) != Room::None){
                posDungeon.y += 1;
            }
            break;

        case Orientation::South:
            if (getRoomType(posDungeon.x + 1, posDungeon.y) != Room::None){
                posDungeon.x += 1;
            }
            break;

        case Orientation::West:
            if (getRoomType(posDungeon.x, posDungeon.y - 1) != Room::None){
                posDungeon.y -= 1;
            }
            break;

        default:
            break;
    }
}

/******************
 * GetDungeonSize *
 ******************/
unsigned Dungeon::getDungeonSize() const{

    return information[0].at(0);
}

/*****************
 * SetPosDungeon *
 *****************/
void Dungeon::setPosDungeon(unsigned i, unsigned j){

    if((j >= 0 && i >= 0) && (j < information[0].at(0) && i < information[0].at(0))){
        if (getRoomType(i, j) != Room::None){
            posDungeon.x = i;
            posDungeon.y = j;
        }
    }
}

/*****************
 * GetPosDungeon *
 *****************/
sf::Vector2u Dungeon::getPosDungeon() const{

    return posDungeon;
}

bool Dungeon::end() const{

    return actualStage == maxStageNumber - 1;
}

/*******************
 * FillInformation *
 *******************/
void Dungeon::fillInformation(){

    std::ifstream file;
    file.open(filePath);

    if(file.is_open()){
        std::string csvItem;

        while(std::getline(file, csvItem)){

            std::vector<unsigned> vect;
            std::istringstream iss(csvItem);

            vect.push_back(returnCsvItemSTOI(iss));
            vect.push_back(returnCsvItemSTOI(iss));
            vect.push_back(returnCsvItemSTOI(iss));

            information.push_back(vect);
        }
    }
    else
        throw std::runtime_error ("Failed to load " + filePath);

    file.close();
}

/*********************
 * ReturnCsvItemSTOI *
 *********************/
unsigned Dungeon::returnCsvItemSTOI(std::istringstream &ss){
    std::string result;
    std::getline(ss, result, ',');
    return std::stoi(result);
}

/************
 * SetStage *
 ************/
void Dungeon::setStage(){

    currentStage.reset(new Stage(information[0].at(0), information[0].at(1), information[0].at(2), textureMgr));

    information.erase(information.begin());

    currentStage->generate(actualStage);

    unsigned mid = (information[0].at(0) - 1)/2;
    setPosDungeon(mid, mid);

    std::cout << *currentStage;
}
