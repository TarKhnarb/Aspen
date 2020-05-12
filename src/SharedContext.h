#ifndef GAME_SHAREDCONTEXT_H
#define GAME_SHAREDCONTEXT_H

#include "Window.h"
#include "EventManager.h"
#include "TextureManager.h"

struct SharedContext{

    SharedContext():
            wind(nullptr),
            eventManager(nullptr),
            textureManager(nullptr){}

    Window *wind;

    EventManager *eventManager;
    
    TextureManager *textureManager;
};

#endif
