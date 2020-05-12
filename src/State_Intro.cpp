#include "State_Intro.h"
#include "StateManager.h"

/***************
 * Constructor *
 ***************/
State_Intro::State_Intro(StateManager *stateMgr):
    BaseState(stateMgr){}

/**************
 * Destructor *
 **************/
State_Intro::~State_Intro(){}

/************
 * OnCreate *
 ************/
void State_Intro::onCreate(){

    timePassed = 0.0f;
    sf::Vector2u windowSize = stateMgr->getContext()->wind->getWindow()->getSize();

    introTexture.loadFromFile("Data/Textures/Intro/Intro.png");
    introSprite.setTexture(introTexture);
    introSprite.setOrigin(introTexture.getSize().x / 2.0f, introTexture.getSize().y / 2.0f);
    introSprite.setPosition(windowSize.x / 2.0f, 0);

    font.loadFromFile("Data/Fonts/Verdana.ttf");
    text.setFont(font);
    text.setString({"Press SPACE to continue"});
    text.setCharacterSize(15);
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    text.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);

    EventManager *evMgr = stateMgr->getContext()->eventManager;
    evMgr->addCallback(StateType::Intro, "Intro_Continue", &State_Intro::continu,this);
}

/*************
 * OnDestroy *
 *************/
void State_Intro::onDestroy(){

    EventManager *evMgr = stateMgr->getContext()->eventManager;
    evMgr->removeCallback(StateType::Intro,"Intro_Continue");
}

/***********
 * Continu *
 ***********/
void State_Intro::continu(EventDetails *details){

    if(timePassed >= 2.f){
        // stateMgr->switchTo(StateType::MainMenu); // ToDo later set a MainMenu where the player can chose between 3 saves
        stateMgr->switchTo(StateType::Dungeon);
        stateMgr->remove(StateType::Intro);
    }
}

/**********
 * Update *
 **********/
void State_Intro::update(const sf::Time &time){

    if(timePassed < 2.f){

        timePassed += time.asSeconds();
        introSprite.setPosition(introSprite.getPosition().x, introSprite.getPosition().y + (48 * time.asSeconds()));
    }
}

/********
 * Draw *
 ********/
void State_Intro::draw(){

    sf::RenderWindow *window = stateMgr->getContext()->wind->getWindow();
    window->draw(introSprite);

    if(timePassed >= 2.f)
        window->draw(text);
}

/************
 * Activate *
 ************/
void State_Intro::activate(){} // ToDo a voir pour plus tard (pas utile pour l'instant)

/***************
 * Deactivate *
 ***************/
void State_Intro::deactivate(){} // ToDo a voir pour plus tard (pas utile pour l'instant)

