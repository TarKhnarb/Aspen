#include "Stage.h"

/***************
 * Constructor *
 ***************/
Stage::Stage(unsigned size, unsigned minRoom, unsigned maxRoom):
        stageSize(size),
        minRoomCount(minRoom),
        maxRoomCount(maxRoom){

    for(unsigned i = 0; i < stageSize; ++i){

        roomMap.emplace_back();
        for(unsigned j = 0; j < stageSize; ++j){

            roomMap[i].emplace_back(nullptr);
        }
    }
}

/************
 * Generate *
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

                    if ((roomsCnt < roomsNb - 1) && (rand()%entropy == entropy - 1)){ // Place une salle seulement si le mod est différent de 0

                        roomMap[i][mid - k].reset(new Room());
                        ++roomsCnt;
                    }
                }
            }

            if(roomMap[mid - k + 1][mid - k]){ // Traitement de la case tout en haut à gauche

                if((roomsCnt < roomsNb - 1) && (rand()%entropy == entropy - 1)){

                    roomMap[mid - k][mid - k].reset(new Room());
                    ++roomsCnt;
                }
            }

            for(unsigned j = mid - k + 1; j <= mid + k - 1; ++j){ // Deuxième ligne, à droite à la verticale

                if((j > 0 && roomMap[mid + k][j - 1]) || roomMap[mid + k - 1][j]){ // Test sur les cases au dessus et à gauche

                    if((roomsCnt < roomsNb - 1) && (rand()%entropy == entropy - 1)){

                        roomMap[mid + k][j].reset(new Room());
                        ++roomsCnt;
                    }
                }
            }

            for(unsigned j = mid - k + 1; j <= mid + k - 1; ++j){ // Troisième ligne, à gauche à la verticale

                if((j > 0 && roomMap[mid - k][j - 1]) || (roomMap[mid - k + 1][j])){ // test sur les cases au dessus et à droite

                    if((roomsCnt < roomsNb-1) && (rand()%entropy == entropy - 1)){

                        roomMap[mid - k][j].reset(new Room());
                        ++roomsCnt;
                    }
                }
            }

            for(unsigned i = mid - k; i <= mid + k; ++i){ // Dernière ligne, en bas à l'horizontal

                if((i + 1 < stageSize && roomMap[i + 1][mid + k]) || roomMap[i][mid + k - 1]){ // Test de la case à gauche et au dessus

                    if((roomsCnt < roomsNb - 1) && (rand()%entropy == entropy - 1)){

                        roomMap[i][mid + k].reset(new Room());
                        ++roomsCnt;
                    }
                }
            }

            /*
             * La salle du boss
             */

            if(roomsCnt == roomsNb - 1){

                for(unsigned i = mid - k + 1; i <= mid + k; ++i){ // Première ligne, en haut à l'horizontal, sauf case tout en haut à gauche

                    if((!roomMap[i][mid - k]) && (checkRoomAround(i, mid - k) == 1)){

                        if((roomsCnt == roomsNb - 1) && (rand()%entropy == entropy - 1)){ // Place une salle seulement si le mod est différent de 0

                            roomMap[i][mid - k].reset(new Room(Room::Boss));
                            ++roomsCnt;
                        }
                    }
                }

                if((!roomMap[mid - k][mid - k]) && (checkRoomAround(mid - k, mid - k))){ // Traitement de la case tout en haut à gauche

                    if((roomsCnt == roomsNb-1) && (rand()%entropy == entropy - 1)){

                        roomMap[mid - k][mid - k].reset(new Room(Room::Boss));
                        ++roomsCnt;
                    }
                }

                for(unsigned j = mid - k + 1; j <= mid + k - 1; ++j){ // Deuxième ligne, à droite à la verticale

                    if((!roomMap[mid + k][j]) && (checkRoomAround(mid + k, j))){

                        if((roomsCnt == roomsNb - 1) && (rand()%entropy == entropy - 1)){

                            roomMap[mid + k][j].reset(new Room(Room::Boss));
                            ++roomsCnt;
                        }
                    }
                }

                for(unsigned j = mid - k + 1; j <= mid + k - 1; ++j){ // Troisième ligne, à gauche à la verticale

                    if((!roomMap[mid - k][j]) && (checkRoomAround(mid - k, j))){

                        if((roomsCnt == roomsNb - 1) && (rand()%entropy == entropy - 1)){

                            roomMap[mid - k][j].reset(new Room(Room::Boss));
                            ++roomsCnt;
                        }
                    }
                }

                for(unsigned i = mid - k; i <= mid + k; ++i){ // Dernière ligne, en bas à l'horizontal

                    if((!roomMap[i][mid + k]) && (checkRoomAround(i, mid + k))){

                        if((roomsCnt == roomsNb - 1) && (rand()%entropy == entropy - 1)){

                            roomMap[i][mid + k].reset(new Room(Room::Boss));
                            roomsCnt ++;
                        }
                    }
                }
            }
        }
    }

    ++stageNumber;

    placeDoors();
}

/***********
 * GetRoom *
 ***********/
Room* Stage::getRoom(unsigned i, unsigned j) const{

    return roomMap[i][j].get();
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
        roomMap[mid][mid].reset(new Room(Room::CommonStart));
    else
        roomMap[mid][mid].reset(new Room(Room::Start));
}

/*******************
 * CheckRoomAround *
 *******************/
bool Stage::checkRoomAround(unsigned i, unsigned j) { // prend les coords d'une case et retourne le nb de salles EXISTANTES autour

    unsigned count = 0;

    if(i > 0){
        
        if(roomMap[i - 1][j]) // Left Room
            ++count;
    }

    if(j > 0){
        
        if(roomMap[i][j - 1]) // Room above
            ++count;
    }

    if(i + 1 < stageSize){
        
        if(roomMap[i + 1][j]) // Right Room
            ++count;
    }

    if(j + 1 < stageSize){
        
        if(roomMap[i][j + 1]) // Room below
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

                if((i > 0) && (roomMap[i - 1][j])) // Room above
                    roomMap[i][j]->addDoor(Orientation::North);

                if ((j > 0) && (roomMap[i][j - 1])) // Left Room
                    roomMap[i][j]->addDoor(Orientation::West);

                if((i + 1) < (stageSize && roomMap[i + 1][j])) // Room below
                    roomMap[i][j]->addDoor(Orientation::South);

                if((j + 1 < stageSize) && (roomMap[i][j + 1])) // Right Room
                    roomMap[i][j]->addDoor(Orientation::East);
            }
        }
    }
}


/****************
 * Graphic View *
 ***************/
std::ostream& operator<<(std::ostream& stream, const Stage &s){

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

                    case Room::CommonStart:
                        stream << "s";
                        break;

                    case Room::Room2WE1 :
                        stream << "A";
                        break;

                    case Room::Room2WE2 :
                        stream << "B";
                        break;

                    case Room::Room2NS1 :
                        stream << "C";
                        break;

                    case Room::Room2NS2 :
                        stream << "D";
                        break;

                    case Room::Room4NESW1:
                        stream << "E";
                        break;

                    case Room::Room4NESW2:
                        stream << "F";
                        break;

                    case Room::Room1N:
                        stream << "G";
                        break;

                    case Room::Room1E:
                        stream << "H";
                        break;

                    case Room::Room1S:
                        stream << "I";
                        break;

                    case Room::Room1W :
                        stream << "J";
                        break;

                    case Room::Room3NEW:
                        stream << "K";
                        break;

                    case Room::Room3NSW:
                        stream << "L";
                        break;

                    case Room::Room3ESW:
                        stream << "M";
                        break;

                    case Room::Room3NES:
                        stream << "N";
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