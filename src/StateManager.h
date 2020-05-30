#ifndef GAME_STATEMANAGER_H
#define GAME_STATEMANAGER_H

#include <SFML/Graphics.hpp>

#include <vector>
#include <unordered_map>
#include <functional>

#include "SharedContext.h"
#include "States/State_Intro.h"
#include "States/State_Dungeon.h"
#include "States/State_GamePause.h"
#include "States/State_Map.h"
#include "States/State_GameOver.h"
#include "States/State_Statistics.h"

enum class StateType{

    Intro = 1,
    MainMenu,
    KeyboardMenu,
    Dungeon,
    GamePause,
    Map,
    Base,
    Statistics,
    Inventory,
    Npc,
    GameOver,
    MiniMap
};

using StateContainer = std::vector<std::pair<StateType, BaseState*>>;

using TypeContainer = std::vector<StateType>;

using StateFactory = std::unordered_map<StateType, std::function<BaseState*(void)>>;

class StateManager{

public:

    StateManager(SharedContext *shared);
    ~StateManager();

public:

    void update(const sf::Time &time);

    void draw();

    void processRequests();

    SharedContext* getContext() const;

    bool hasState(const StateType &type);

    void switchTo(const StateType &type);

    void remove(const StateType &type);

private:

    void createState(const StateType &type);

    void removeState(const StateType &type);

    template<class T>
    void registerState(const StateType &type){

        stateFactory[type] = [this]() -> BaseState*{

            return new T(this);
        };
    }

private:

    SharedContext *shared;
    StateContainer states;
    TypeContainer toRemove;
    StateFactory stateFactory;
};

#endif
