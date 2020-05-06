#include "Rock.h"

Rock::Rock(unsigned number):
        life (number){

    selectForm();
}

void Rock::hit(unsigned damage){

    life -= damage;
}


bool Rock::getState() const{

    return life !=0;
}

unsigned Rock::getLife() const{

    return life;
}

unsigned Rock::getForm() const{

    return form;
}

void Rock::selectForm(){

    form = rand()%3;
}