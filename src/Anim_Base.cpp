#include "Anim_Base.h"
#include "SpriteSheet.h"

/***************
 * Constructor *
 ***************/
Anim_Base::Anim_Base():
        frameCurrent(0),
        frameStart(0),
        frameEnd(0),
        frameRow(0),
        frameTime(0.f),
        elapsedTime(0.f),
        frameActionStart(-1),
        frameActionEnd(-1),
        loop(false),
        playing(false){}

/**************
 * Destructor *
 **************/
Anim_Base::~Anim_Base(){}

/******************
 * SetSpriteSheet *
 ******************/
void Anim_Base::setSpriteSheet(SpriteSheet *sheet){

    spriteSheet = sheet;
}

/************
 * SetFrame *
 ************/
void Anim_Base::setFrame(const unsigned int &frame){

    if((frame >= frameStart && frame <= frameEnd) || (frame >= frameEnd && frame <= frameStart))
        frameCurrent = frame;
}

/***********
 * SetName *
 ***********/
void Anim_Base::setName(const std::string tName){

    name = tName;
}

/**************
 * SetLooping *
 **************/
void Anim_Base::setLooping(const bool isLooping){

    loop = isLooping;
}

/**************
 * IsInAction *
 **************/
bool Anim_Base::isInAction(){
    if(frameActionStart == -1 || frameActionEnd == -1)
        return true;

    return (frameCurrent >= frameActionStart && frameCurrent <= frameActionEnd);
}

/********
 * Play *
 ********/
void Anim_Base::play(){

    playing = true;
}

/*********
 * Pause *
 *********/
void Anim_Base::pause(){

    playing = false;
}

/********
 * Stop *
 ********/
void Anim_Base::stop(){

    playing = false;
    reset();
}

/*********
 * Reset *
 *********/
void Anim_Base::reset(){

    frameCurrent = frameStart;
    elapsedTime = 0.0f;
    cropSprite();
}

/**********
 * Update *
 **********/
void Anim_Base::update(const float &deltaT){

    if (!playing)
        return;

    elapsedTime += deltaT;
    if (elapsedTime < frameTime)
        return;

    frameStep();
    cropSprite();
    elapsedTime = 0;
}