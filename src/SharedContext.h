#ifndef GAME_SHAREDCONTEXT_H
#define GAME_SHAREDCONTEXT_H

struct SharedContext{

    SharedContext():
            wind(nullptr),
            eventManager(nullptr){}

    Window *wind;

    EventManager *eventManager;
};

#endif
