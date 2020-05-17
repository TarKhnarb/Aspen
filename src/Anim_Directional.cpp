#include "Anim_Directional.h"
#include "SpriteSheet.h"

/*************
 * FrameStep *
 *************/
void Anim_Directional::frameStep(){

    if(frameStart < frameEnd)
        ++frameCurrent;

    else if(frameStart > frameEnd)
        --frameCurrent;

    if((frameStart < frameEnd && frameCurrent > frameEnd) || (frameStart > frameEnd && frameCurrent < frameEnd)){

        if (loop){

            frameCurrent = frameStart;
            return;
        }
        frameCurrent = frameEnd;
        pause();
    }
}

/**************
 * CropSprite *
 **************/
void Anim_Directional::cropSprite(){

    sf::IntRect rect(
            spriteSheet->getSpriteSize().x * frameCurrent,
            spriteSheet->getSpriteSize().y * (frameRow + (short)spriteSheet->getOrientation()),
            spriteSheet->getSpriteSize().x,
            spriteSheet->getSpriteSize().y);

    spriteSheet->cropSprite(rect);
}

/**********
 * ReadIn *
 ****é******/
void Anim_Directional::readIn(std::stringstream &stream){

    stream >> frameStart >> frameEnd >> frameRow >> frameTime >> frameActionStart >> frameActionEnd;
}
