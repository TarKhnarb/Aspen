#include "Rock.h"

Rock::Rock(unsigned number):
        life (number){

    selectForm();
}

void Rock::hit(unsigned damage){

    if(life >= damage)
        life -= damage;
    else
        life = 0;
}

bool Rock::getState() const{

    return life != 0;
}

unsigned Rock::getForm() const{

    return form;
}

void Rock::selectForm(){

    form = rand()%3;
}