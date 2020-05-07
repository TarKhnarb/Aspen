#include "Dungeon.h"

Dungeon::Dungeon():
        actualStage(0),
        filePath("Data/Files/Dungeon/DungeonInformations.csv"){

    fillInformation();
    maxStageNumber = information.size();

    setStage();
}

void Dungeon::nextStage(){

    if(actualStage < maxStageNumber)
        setStage();
    else
        throw std::out_of_range("Dungeon::nextStage() : Vous avez atteint la fin du donjon, etage " + std::to_string(actualStage));
}

Room* Dungeon::getRoom(unsigned i, unsigned j) const{

    if(currentStage)
        return currentStage->getRoom(i, j);
    else
        throw std::domain_error("Dungeon::getRoom() : The room you are referring to does not exist, coordonate (" + std::to_string(i) + ", " + std::to_string(j) + ")");
}

void Dungeon::setStage(){

    currentStage.reset(new Stage(information[0].at(0), information[0].at(1), information[0].at(2)));

    information.erase(information.begin());

    currentStage->generate(actualStage);

    std::cout << *currentStage;
}

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

unsigned Dungeon::returnCsvItemSTOI(std::istringstream &ss){
    std::string result;
    std::getline(ss, result, ',');
    return std::stoi(result);
}