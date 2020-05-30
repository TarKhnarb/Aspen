#ifndef GAME_SHAREDCONTEXT_H
#define GAME_SHAREDCONTEXT_H

#include "Window.h"
#include "EventManager.h"
#include "TextureManager.h"
#include "Entity/Player.h"

class Projectile;

struct SharedContext{

    SharedContext():
            wind(nullptr),
            eventManager(nullptr),
            textureManager(nullptr),
            aspen(nullptr){}

    Window *wind;

    EventManager *eventManager;
    
    TextureManager *textureManager;
    
    Player* aspen;
};

#endif
