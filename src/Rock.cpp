#include "Rock.h"

/***************
 * Constructor *
 ***************/
Rock::Rock(unsigned life):
        life (life){

    selectForm();
}

/*******
 * Hit *
 *******/
void Rock::hit(unsigned damage){

    if(life >= damage)
        life -= damage;
    else
        life = 0;
}

/************
 * GetState *
 ************/
bool Rock::getState() const{

    return life != 0;
}

/***********
 * GetForm *
 ***********/
unsigned Rock::getForm() const{

    return form;
}

/**************
 * SelectForm *
 **************/
void Rock::selectForm(){

    form = rand()%3;
}