#ifndef GAME_BASESTATE_H
#define GAME_BASESTATE_H

class StateManager;

class BaseState{

    friend class StateManager;

public:

    BaseState(StateManager *stateManager):
            stateMgr(stateManager),
            transparent(false),
            transcendent(false){}

    virtual ~BaseState(){}

public:

    virtual void onCreate() = 0;

    virtual void onDestroy() = 0;

    virtual void activate() = 0;

    virtual void deactivate() = 0;

    virtual void update(const sf::Time &time) = 0;

    virtual void draw() = 0;

    void setTransparent(const bool &transp){

        transparent = transp;
    }

    bool isTransparent()const{

        return transparent;
    }

    void setTranscendent(const bool &transc){

        transcendent = transc;
    }

    bool isTranscendent()const{

        return transcendent;
    }

    StateManager* getStateManager(){

        return stateMgr;
    }

    sf::View& getView(){

        return view;
    }

protected:

    StateManager *stateMgr;
    bool transparent;
    bool transcendent;
    sf::View view;
};

#endif