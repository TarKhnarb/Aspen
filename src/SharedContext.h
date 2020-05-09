#ifndef GAME_SHAREDCONTEXT_H
#define GAME_SHAREDCONTEXT_H

#include "Window.h"
#include "EventManager.h"

#include "EventManager.h"
#include "Window.h"

struct SharedContext{

    SharedContext():
            wind(nullptr),
            eventManager(nullptr){}

    Window *wind;

    EventManager *eventManager;
};

#endif
