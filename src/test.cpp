#include <iostream>

#include "Dungeon.h"

int main(){
    unsigned i, j;

    Dungeon test;

    std::cout << "Entrer les coordonnées d'une salle" << std::endl;

    std::cin >> i >> j;
    std::cout << std::endl;

    test.getRoom(i, j)->display();
}