#ifndef GAME_ROCK_H
#define GAME_ROCK_H

#include <iostream>

class Rock{

public:

    Rock(unsigned number);

public: // Functions

    void hit(unsigned damage);

    bool getState() const;

    unsigned getLife() const;

    unsigned getForm() const;

private: // Functions

    void selectForm();

private: // Variables

    unsigned life;

    unsigned form;

};

#endif