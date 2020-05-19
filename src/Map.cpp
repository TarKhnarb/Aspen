#include "Map.h"

Map::Map(TextureManager *txtMng):
        txtMng(txtMng),
        spawnPoint(1220.f, 520.f){

    background.setSize({2560.f, 1440.f});
    background.setFillColor(sf::Color(148, 223, 231));;

    txtMng->requireResource("Map");
    map.setTexture(*txtMng->getResource("Map"));
    map.setScale({1280.f/4000.f, 720.f/2250.f});
    map.setPosition(640.f, 360.f);

    placeWalls();
}

Map::~Map(){}

Entity::Type Map::checkMapCollisions(Entity &entity){

    for(const auto &wall : walls){

        entity.collides(*wall, 0.f);
    }
    
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


void Map::draw(sf::RenderTarget &target, sf::RenderStates state) const{

    target.draw(background, state);
    target.draw(map, state);
}
