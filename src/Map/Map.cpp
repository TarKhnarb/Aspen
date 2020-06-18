#include "Map.h"

Map::Map(TextureManager *txtMng):
        txtMng(txtMng),
        dungeonDoor(Wall(sf::FloatRect(1682.f, 518.f, 32.f, 32.f))),
        spawnPoint(1220.f, 520.f){

    background.setSize({2560.f, 1440.f});
    background.setFillColor(sf::Color(148, 223, 231));;

    txtMng->requireResource("Map");
    map.setTexture(*txtMng->getResource("Map"));
    map.setScale({1280.f/4000.f, 720.f/2250.f});
    map.setPosition(640.f, 360.f);

    placeWalls();
    placeHouses();
}

Map::~Map(){
    
    txtMng->releaseResource("Map");
}

Entity::Type Map::checkMapCollisions(Entity &entity){

    for(const auto &wall : walls)
        entity.collides(*wall, 0.f);

    for(const auto &house : houses)
        entity.collides(*house, 0.f);

    if(entity.collides(dungeonDoor, 0.f))
        return Entity::Wall;

    return Entity::None;
}

sf::Vector2f Map::getSpawnPoint() const{

    return spawnPoint;
}

void Map::placeWalls(){

    std::ifstream file;
    std::string filename("Data/Files/Map/Wall.cfg");
    file.open(filename);

    std::string line;
    if(file.is_open()){

        std::size_t lineNb = 0;
        while(!file.eof()){

            getline(file, line);
            for(std::size_t i = 0; i < line.size(); ++i){

                if(std::stoi(line.substr(i, 1)) == 1){

                    std::unique_ptr<Wall> wall (new Wall(16.f * i, 16.f * lineNb, 16.f, 16.f));
                    walls.push_back(std::move(wall));
                }
            }
            ++lineNb;
        }

    }
    else
        throw std::runtime_error ("Failed to load " + filename);

    file.close();
}

void Map::placeHouses(){

    std::ifstream file;
    std::string filename("Data/Files/Map/Houses.cfg");
    file.open(filename);

    std::string line;
    if(file.is_open()){

        while(!file.eof()){

            std::string line;
            std::getline(file, line);
            std::istringstream sLine(line);

            std::string readName, coordX, coordY;

            sLine >> readName >> coordX >> coordY;

            if(readName == "Base"){

                std::unique_ptr<House> house(new House("BaseHouse" ,txtMng));
                house->setPosition(static_cast<float>(std::stoi(coordX)), static_cast<float>(std::stoi(coordY)));
                houses.push_back(std::move(house));
            }
            else if(readName == "Dungeon"){

                std::unique_ptr<House> house(new House("Dungeon" ,txtMng));
                house->setPosition(static_cast<float>(std::stoi(coordX)), static_cast<float>(std::stoi(coordY)));
                houses.push_back(std::move(house));
            }
            else if(readName == "Blacksmith"){

                std::unique_ptr<House> house(new House("BlacksmithHouse" ,txtMng));
                house->setPosition(static_cast<float>(std::stoi(coordX)), static_cast<float>(std::stoi(coordY)));
                houses.push_back(std::move(house));
            }
            else if(readName == "Witch"){

                std::unique_ptr<House> house(new House("WitchHouse" ,txtMng));
                house->setPosition(static_cast<float>(std::stoi(coordX)), static_cast<float>(std::stoi(coordY)));
                houses.push_back(std::move(house));
            }
            else if(readName == "Crafter"){

                std::unique_ptr<House> house(new House("CrafterHouse" ,txtMng));
                house->setPosition(static_cast<float>(std::stoi(coordX)), static_cast<float>(std::stoi(coordY)));
                houses.push_back(std::move(house));
            }
            else if(readName == "Trader"){

                std::unique_ptr<House> house(new House("TraderHouse" ,txtMng));
                house->setPosition(static_cast<float>(std::stoi(coordX)), static_cast<float>(std::stoi(coordY)));
                houses.push_back(std::move(house));
            }
        }
    }
    else
        throw std::runtime_error ("Failed to load " + filename);

    file.close();
}

void Map::draw(sf::RenderTarget &target, sf::RenderStates states) const{

    target.draw(background, states);
    target.draw(map, states);

    for(const auto &house : houses)
        target.draw(*house, states);
}
