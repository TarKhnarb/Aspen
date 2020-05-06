#include <iostream>

#include "Stage.h"

int main(){

    unsigned stageNb = 0;

    Stage stage(21, 10, 15);
    stage.generate(stageNb);

    std::cout << stage;
}