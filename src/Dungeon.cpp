#include "Dungeon.h"

/***************
 * Constructor *
 ***************/
Dungeon::Dungeon():
        actualStage(0),
        filePath("Data/Files/Dungeon/DungeonInformations.csv"){

    fillInformation();
    maxStageNumber = information.size();

    unsigned mid = (information[0].at(0) - 1)/2;
    posDungeon = std::make_pair(mid, mid);

    setStage();
}

/*************
 * NextStage *
 *************/
void Dungeon::nextStage(){

    if(actualStage < maxStageNumber)
        setStage();
    else
        throw std::out_of_range("Dungeon::nextStage() : Vous avez atteint la fin du donjon, etage " + std::to_string(actualStage));
}

/***********
 * GetRoom *
 ***********/
Room* Dungeon::getRoom(unsigned i, unsigned j) const{

    if(currentStage)
        return currentStage->getRoom(i, j);
    else
        throw std::domain_error("Dungeon::getRoom() : The room you are referring to does not exist, coordonate (" + std::to_string(i) + ", " + std::to_string(j) + ")");
}

/**************
 * ChangeRoom *
 **************/
Room* Dungeon::changeRoom(Orientation orient){

    switch(orient){
        case Orientation::North:
            return getRoom(posDungeon.first, posDungeon.second - 1);

        case Orientation::East:
            return getRoom(posDungeon.first + 1, posDungeon.second);

        case Orientation::South:
            return getRoom(posDungeon.first, posDungeon.second + 1);

        case Orientation::West:
            return getRoom(posDungeon.first - 1, posDungeon.second);

        default:
            break;//return getRoom(posDungeon.first, posDungeon.second);
    }
}

/*****************
 * SetPosDungeon *
 *****************/
void Dungeon::setPosDungeon(unsigned i, unsigned j){

    if((j >= 0 && i >= 0) && (j < information[0].at(0) && i < information[0].at(0))){

        posDungeon.first = i;
        posDungeon.second = j;
    }
}

/*****************
 * GetPosDungeon *
 *****************/
std::pair<int,int> Dungeon::getPosDungeon() const{

    return posDungeon;
}

/******************
 * GetDungeonSize *
 ******************/
unsigned Dungeon::getDungeonSize(){

    return information[0].at(0);
}

/************
 * SetStage *
 ************/
void Dungeon::setStage(){

    currentStage.reset(new Stage(information[0].at(0), information[0].at(1), information[0].at(2)));

    information.erase(information.begin());

    currentStage->generate(actualStage);

    std::cout << *currentStage;
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