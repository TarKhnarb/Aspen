#include "Bonus.h"

/***************
 * Constructor *
 ***************/
Bonus::Bonus(const std::string &name){

    absolute.fill(0.f);
    relative.fill(1.f);

    loadFromFile(name);
}

/****************
 * LoadFromFile *
 ****************/
void Bonus::loadFromFile(const std::string &name){

    std::string filename = "Data/Files/Objects/" + name + ".cfg";

    std::ifstream file(filename);
    if(!file.is_open()){

        throw std::runtime_error("Failed to load " + filename);
    }

    while(!file.eof()){

        std::string line;
        std::getline(file, line);
        std::istringstream sLine(line);

        std::string statName;
        std::string statAbs;
        std::string statRel;

        sLine >> statName >> statAbs >> statRel;

        if(statName == "Life"){

            absolute[static_cast<int>(StatName::Life)] += std::stoi(statAbs);
            relative[static_cast<int>(StatName::Life)] *= std::stoi(statRel);
        }
        else if(statName == "Attack"){

            absolute[static_cast<int>(StatName::Attack)] += std::stoi(statAbs);
            relative[static_cast<int>(StatName::Attack)] *= std::stoi(statRel);
        }
        else if(statName == "AttackSpeed"){

            absolute[static_cast<int>(StatName::AttackSpeed)] += std::stoi(statAbs);
            relative[static_cast<int>(StatName::AttackSpeed)] *= std::stoi(statRel);
        }
        else if(statName == "ProjectileSpeed"){

            absolute[static_cast<int>(StatName::ProjectileSpeed)] += std::stoi(statAbs);
            relative[static_cast<int>(StatName::ProjectileSpeed)] *= std::stoi(statRel);
        }
        else if(statName == "Defence"){

            absolute[static_cast<int>(StatName::Defence)] += std::stoi(statAbs);
            relative[static_cast<int>(StatName::Defence)] *= std::stoi(statRel);
        }
        else if(statName == "Speed"){

            absolute[static_cast<int>(StatName::Speed)] += std::stoi(statAbs);
            relative[static_cast<int>(StatName::Speed)] *= std::stoi(statRel);
        }
        else if(statName == "CanFly"){

            int testAbs = (statAbs == "No") ? 0 : 1;
            int testRel = (statRel == "No") ? 0 : 1;
            absolute[static_cast<int>(StatName::CanFly)] = testAbs;
            relative[static_cast<int>(StatName::CanFly)] = testRel;
        }
    }
}

/*************
 * GetValues *
 *************/
sf::Vector2f Bonus::getValues(StatName stat) const{
    
    sf::Vector2f values;
    
    values.x = absolute[stat];
    values.y = relative[stat];
    
    return values;
}
