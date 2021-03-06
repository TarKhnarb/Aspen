#include "Stage.h"

/***************
 * Constructor *
 ***************/
Stage::Stage(unsigned size, unsigned minRoom, unsigned maxRoom, SharedContext *shared):
        stageSize(size),
        minRoomCount(minRoom),
        maxRoomCount(maxRoom),
        context(shared){

    if(maxRoom >= size*size)
        throw std::invalid_argument("Stage::Stage() : Number of rooms is too big for the given size");

    if(size%2 == 0)
        throw std::invalid_argument("Stage::Stage() : The size of the stage need to be odd " + std::to_string(stageSize));

    for(unsigned i = 0; i < stageSize; ++i){

        roomMap.emplace_back();
        for(unsigned j = 0; j < stageSize; ++j){

            roomMap[i].emplace_back(nullptr);
        }
    }
}

/************
 * Generate * //TODO changer l'utilisation du seed pour que ca soit le donjon qui donne un seed global pour la généraion des étages qui le compose
 ************/
void Stage::generate(unsigned &stageNumber, unsigned seed){

    setSeed(seed);

    unsigned roomsNb = rand()%(maxRoomCount-minRoomCount+1)+minRoomCount;
    unsigned roomsCnt = 0;
    unsigned entropy = 2;

    unsigned mid = (stageSize - 1)/2;

    while (roomsNb != roomsCnt){ // Génère les salles autour de la salle de départ (centre)

        reset(stageNumber); // Reset (nettoie le tableau et genere le depart au milieu du tableau)
        roomsCnt = 0; // Au cas où on recommence

        // Génère les salles du Stage
        for(unsigned k = 1; k <= mid; ++k){ // Chaque 'cercles' autour du point central

            for(unsigned i = mid - k + 1; i <= mid + k; ++i){ // Première ligne, en haut à l'horizontal, sauf case tout en haut à gauche (car rien encore à côté)

                if((i > 0 && roomMap[i - 1][mid - k]) || (roomMap[i][mid - k + 1])){ // Test sur les cases à gauche et en dessous

                    if ((roomsCnt < roomsNb - 2) && (rand()%entropy == entropy - 1)){ // Place une salle seulement si le mod est différent de 0

                        roomMap[i][mid - k].reset(new Room(context));
                        ++roomsCnt;
                    }
                }
            }

            if(roomMap[mid - k + 1][mid - k]){ // Traitement de la case tout en haut à gauche

                if((roomsCnt < roomsNb - 2) && (rand()%entropy == entropy - 1)){

                    roomMap[mid - k][mid - k].reset(new Room(context));
                    ++roomsCnt;
                }
            }

            for(unsigned j = mid - k + 1; j <= mid + k - 1; ++j){ // Deuxième ligne, à droite à la verticale

                if((j > 0 && roomMap[mid + k][j - 1]) || roomMap[mid + k - 1][j]){ // Test sur les cases au dessus et à gauche

                    if((roomsCnt < roomsNb - 2) && (rand()%entropy == entropy - 1)){

                        roomMap[mid + k][j].reset(new Room(context));
                        ++roomsCnt;
                    }
                }
            }

            for(unsigned j = mid - k + 1; j <= mid + k - 1; ++j){ // Troisième ligne, à gauche à la verticale

                if((j > 0 && roomMap[mid - k][j - 1]) || (roomMap[mid - k + 1][j])){ // test sur les cases au dessus et à droite

                    if((roomsCnt < roomsNb - 2) && (rand()%entropy == entropy - 1)){

                        roomMap[mid - k][j].reset(new Room(context));
                        ++roomsCnt;
                    }
                }
            }

            for(unsigned i = mid - k; i <= mid + k; ++i){ // Dernière ligne, en bas à l'horizontal

                if((i + 1 < stageSize && roomMap[i + 1][mid + k]) || roomMap[i][mid + k - 1]){ // Test de la case à gauche et au dessus

                    if((roomsCnt < roomsNb - 2) && (rand()%entropy == entropy - 1)){

                        roomMap[i][mid + k].reset(new Room(context));
                        ++roomsCnt;
                    }
                }
            }

                // Sale de boost
            if(roomsCnt == roomsNb - 2){

                for(unsigned i = mid - k + 1; i <= mid + k; ++i){ // Première ligne, en haut à l'horizontal, sauf case tout en haut à gauche

                    if((!roomMap[i][mid - k]) && (checkRoomAround(i, mid - k))){

                        if((roomsCnt == roomsNb - 2) && (rand()%entropy == entropy - 1)){ // Place une salle seulement si le mod est différent de 0

                            roomMap[i][mid - k].reset(new Room(context, Room::Boost));
                            ++roomsCnt;
                        }
                    }
                }

                if((!roomMap[mid - k][mid - k]) && (checkRoomAround(mid - k, mid - k))){ // Traitement de la case tout en haut à gauche

                    if((roomsCnt == roomsNb - 2) && (rand()%entropy == entropy - 1)){

                        roomMap[mid - k][mid - k].reset(new Room(context, Room::Boost));
                        ++roomsCnt;
                    }
                }

                for(unsigned j = mid - k + 1; j <= mid + k - 1; ++j){ // Deuxième ligne, à droite à la verticale

                    if((!roomMap[mid + k][j]) && (checkRoomAround(mid + k, j))){

                        if((roomsCnt == roomsNb - 2) && (rand()%entropy == entropy - 1)){

                            roomMap[mid + k][j].reset(new Room(context, Room::Boost));
                            ++roomsCnt;
                        }
                    }
                }

                for(unsigned j = mid - k + 1; j <= mid + k - 1; ++j){ // Troisième ligne, à gauche à la verticale

                    if((!roomMap[mid - k][j]) && (checkRoomAround(mid - k, j))){

                        if((roomsCnt == roomsNb - 2) && (rand()%entropy == entropy - 1)){

                            roomMap[mid - k][j].reset(new Room(context, Room::Boost));
                            ++roomsCnt;
                        }
                    }
                }

                for(unsigned i = mid - k; i <= mid + k; ++i){ // Dernière ligne, en bas à l'horizontal

                    if((!roomMap[i][mid + k]) && (checkRoomAround(i, mid + k))){

                        if((roomsCnt == roomsNb - 2) && (rand()%entropy == entropy - 1)){

                            roomMap[i][mid + k].reset(new Room(context, Room::Boost));
                            roomsCnt ++;
                        }
                    }
                }
            }


                //La salle du boss
            if(roomsCnt == roomsNb - 1){

                for(unsigned i = mid - k + 1; i <= mid + k; ++i){ // Première ligne, en haut à l'horizontal, sauf case tout en haut à gauche

                    if((!roomMap[i][mid - k]) && (checkRoomAround(i, mid - k)) && !(checkRoomAround(i, mid - k, Room::Boost))){

                        if((roomsCnt == roomsNb - 1) && (rand()%entropy == entropy - 1)){ // Place une salle seulement si le mod est différent de 0

                            roomMap[i][mid - k].reset(new Room(context, Room::Boss));
                            ++roomsCnt;
                        }
                    }
                }

                if((!roomMap[mid - k][mid - k]) && (checkRoomAround(mid - k, mid - k)) && !(checkRoomAround(mid - k, mid - k, Room::Boost))){ // Traitement de la case tout en haut à gauche

                    if((roomsCnt == roomsNb - 1) && (rand()%entropy == entropy - 1)){

                        roomMap[mid - k][mid - k].reset(new Room(context, Room::Boss));
                        ++roomsCnt;
                    }
                }

                for(unsigned j = mid - k + 1; j <= mid + k - 1; ++j){ // Deuxième ligne, à droite à la verticale

                    if((!roomMap[mid + k][j]) && (checkRoomAround(mid + k, j)) && !(checkRoomAround(mid + k, j, Room::Boost))){

                        if((roomsCnt == roomsNb - 1) && (rand()%entropy == entropy - 1)){

                            roomMap[mid + k][j].reset(new Room(context, Room::Boss));
                            ++roomsCnt;
                        }
                    }
                }

                for(unsigned j = mid - k + 1; j <= mid + k - 1; ++j){ // Troisième ligne, à gauche à la verticale

                    if((!roomMap[mid - k][j]) && (checkRoomAround(mid - k, j)) && !(checkRoomAround(mid - k, j, Room::Boost))){

                        if((roomsCnt == roomsNb - 1) && (rand()%entropy == entropy - 1)){

                            roomMap[mid - k][j].reset(new Room(context, Room::Boss));
                            ++roomsCnt;
                        }
                    }
                }

                for(unsigned i = mid - k; i <= mid + k; ++i){ // Dernière ligne, en bas à l'horizontal

                    if((!roomMap[i][mid + k]) && (checkRoomAround(i, mid + k)) && !(checkRoomAround(i, mid + k, Room::Boost))){

                        if((roomsCnt == roomsNb - 1) && (rand()%entropy == entropy - 1)){

                            roomMap[i][mid + k].reset(new Room(context, Room::Boss));
                            roomsCnt ++;
                        }
                    }
                }
            }
        }
    }

    ++stageNumber;

    placeDoors();

    affectRoomsType();
}

/***********
 * GetRoom *
 ***********/
Room* Stage::getRoom(unsigned i, unsigned j) const{

    if(roomMap[i][j])
        return roomMap[i][j].get();
    else
        return nullptr;
}

/***********
 * GetSize *
 ***********/
unsigned Stage::getSize() const{

    return stageSize;
}

/***********
 * SetSeed *
 ***********/
void Stage::setSeed(unsigned seed){

    if(seed == 1)
        stageSeed = time(0);
    else
        stageSeed = seed;

    srand(stageSeed);
}

/*********
 * Reset *
 ********/
void Stage::reset(unsigned stage){

    for(unsigned i = 0; i < stageSize; ++i){

        for(unsigned j = 0; j < stageSize; ++j) {

            if(roomMap[i][j])
                roomMap[i][j].release();
        }
    }

    unsigned mid = (stageSize - 1)/2;

    if(stage == 0)
        roomMap[mid][mid].reset(new Room(context, Room::Start));
    else
        roomMap[mid][mid].reset(new Room(context, Room::CommonStart));
}

/*******************
 * CheckRoomAround *
 *******************/
bool Stage::checkRoomAround(unsigned i, unsigned j, Room::Type type) { // prend les coords d'une case et retourne le nb de salles EXISTANTES autour

    unsigned count = 0;

    if(i > 0){
        
        if(roomMap[i - 1][j] && (roomMap[i - 1][j]->getType() == type)) // Left Room
            ++count;
    }

    if(j > 0){
        
        if(roomMap[i][j - 1] && (roomMap[i][j - 1]->getType() == type)) // Room above
            ++count;
    }

    if(i + 1 < stageSize){
        
        if(roomMap[i + 1][j] && (roomMap[i + 1][j]->getType() == type)) // Right Room
            ++count;
    }

    if(j + 1 < stageSize){
        
        if((roomMap[i][j + 1]) && (roomMap[i][j + 1]->getType() == type)) // Room below
            ++count;
    }

    return (count == 1);
}

/**************
 * PlaceDoors *
 **************/
void Stage::placeDoors(){

    for(unsigned i = 0; i < stageSize; ++i){

        for(unsigned j = 0; j < stageSize; ++j){

            if(roomMap[i][j]){

                if((i > 0) && (roomMap[i - 1][j])){ // Room above

                    if(roomMap[i - 1][j]->getType() == Room::Boost)
                        roomMap[i][j]->addDoor(Orientation::North, Door::State::Key);
                    else
                        roomMap[i][j]->addDoor(Orientation::North);
                }

                if ((j > 0) && (roomMap[i][j - 1])){ // Left Room

                    if(roomMap[i][j - 1]->getType() == Room::Boost)
                        roomMap[i][j]->addDoor(Orientation::West, Door::State::Key);
                    else
                        roomMap[i][j]->addDoor(Orientation::West);
                }

                if((i + 1 < stageSize) && (roomMap[i + 1][j])){ // Room below

                    if(roomMap[i + 1][j]->getType() == Room::Boost)
                        roomMap[i][j]->addDoor(Orientation::South, Door::State::Key);
                    else
                        roomMap[i][j]->addDoor(Orientation::South);
                }

                if((j + 1 < stageSize) && (roomMap[i][j + 1])){ // Right Room

                    if(roomMap[i][j + 1]->getType() == Room::Boost)
                        roomMap[i][j]->addDoor(Orientation::East, Door::State::Key);
                    else
                        roomMap[i][j]->addDoor(Orientation::East);
                }
            }
        }
    }
    unsigned mid = (stageSize - 1)/2;
    roomMap[mid][mid]->openDoors();
}

/*******************
 * AffectRoomsType *
 *******************/
void Stage::affectRoomsType(){

    for(auto &col : roomMap){

        for(auto &room : col){

            if(room){
                if(room->getType() == Room::Common)
                    room->affectType(stageSeed);
                room->placeTiles();
            }
        }
    }
}

/****************
 * Graphic View *
 ***************/
std::ostream& operator<<(std::ostream& stream, Stage &s){

    for(unsigned i = 0; i < s.getSize(); ++i){

        for(unsigned j = 0; j < s.getSize(); ++j){

            if(!s.getRoom(i, j))
                stream << ".";

            else{
                switch(s.getRoom(i, j)->getType()){
                    case Room::Common:
                        stream << "c";
                        break;

                    case Room::Start:
                        stream << "S";
                        break;

                    case Room::Boss:
                        stream << "Z";
                        break;

                    case Room::Boost:

                        stream << "b";
                        break;

                    case Room::CommonStart:
                        stream << "s";
                        break;

                    case Room::WE1 :
                        stream << "A";
                        break;

                    case Room::WE2 :
                        stream << "B";
                        break;

                    case Room::NS1 :
                        stream << "C";
                        break;

                    case Room::NS2 :
                        stream << "D";
                        break;

                    case Room::NESW1:
                        stream << "E";
                        break;

                    case Room::NESW2:
                        stream << "F";
                        break;

                    case Room::N:
                        stream << "G";
                        break;

                    case Room::E:
                        stream << "H";
                        break;

                    case Room::S:
                        stream << "I";
                        break;

                    case Room::W :
                        stream << "J";
                        break;

                    case Room::NEW:
                        stream << "K";
                        break;

                    case Room::NSW:
                        stream << "L";
                        break;

                    case Room::ESW:
                        stream << "M";
                        break;

                    case Room::NES:
                        stream << "N";
                        break;
                    
                    case Room::NE:
                        stream << "O";
                        break;
                    
                    case Room::ES:
                        stream << "P";
                        break;
                    
                    case Room::SW:
                        stream << "Q";
                        break;
                    
                    case Room::NW:
                        stream << "R";
                        break;
                    
                    default:
                        break;
                }
            }
        }
        stream << std::endl;
    }

    return stream;
}
