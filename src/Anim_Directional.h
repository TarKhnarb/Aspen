#ifndef GAME_ANIM_DIRECTIONAL_H
#define GAME_ANIM_DIRECTIONAL_H

#include "Anim_Base.h"

class Anim_Directional: public Anim_Base{

protected:

    void frameStep();
    void cropSprite();
    void readIn(std::stringstream &stream);
};

#endif