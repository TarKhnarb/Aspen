#ifndef GAME_ROOM_H
#define GAME_ROOM_H

#include <SFML/Graphics/Color.hpp>

#include <map>
#include <vector>
#include <utility>
#include <cassert>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "Orientation.h"
#include "Rock.h"
#include "Hole.h"
#include "Wall.h"
#include "Door.h"

class Room : public sf::Drawable{

public:

    enum Type{

        Common = 0,
        Start,
        CommonStart,
        Boss,
        Boost,
        N,
        E,
        S,
        W,
        NS1,
        NS2,
        WE1,
        WE2,
        NE,
        ES,
        SW,
        NW,
        NES,
        ESW,
        NSW,
        NEW,
        NESW1,
        NESW2,
        None
    };

    enum class Tile{

        Nothing = 0,
        Hole,
        Rock,
        Chest,
        Boost
    };

public:

    Room(const Room&) = delete;

    Room(TextureManager*, Type roomType = Type::Common);
    ~Room();

public: // Functions

    void setType(Type roomType);

    Type getType() const;

    void addDoor(const Orientation &orient, const Door::State &state = Door::State::Closed);

    void openDoors();

    void closeDoors();

    void affectType(unsigned seed);
    
    void makeRoomTiles();

private:

    std::string takeTilesPath(int roomId); // return Room path witch type corresponding

    void draw(sf::RenderTarget&, sf::RenderStates) const override;
    
private: // Variables

    std::vector<std::unique_ptr<Door>> doors;

    Type type;
    
    std::vector<std::unique_ptr<Entity>> entities;
    
    sf::Sprite sprite;
    
    TextureManager* textureMgr;
};

#endif
