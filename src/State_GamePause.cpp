#include "State_GamePause.h"
#include "StateManager.h"

State_GamePause::State_GamePause(StateManager* stateMgr):
    BaseState(stateMgr){}

State_GamePause::~State_GamePause(){}

void State_GamePause::onCreate(){

    setTransparent(true);

    font.loadFromFile("Data/Fonts/Verdana.ttf");
    text.setFont(font);
    text.setString(sf::String("PAUSED"));
    text.setCharacterSize(28);
    text.setStyle(sf::Text::Bold);

    sf::Vector2u windowSize = stateMgr->getContext()->wind->getWindow()->getSize();

    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    text.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);
    rect.setSize(sf::Vector2f(windowSize));
    rect.setPosition(0,0);
    rect.setFillColor(sf::Color(0,0,0,150));

    EventManager *evMgr = stateMgr->getContext()->eventManager;

    evMgr->addCallback(StateType::GamePause,"GamePause",&State_GamePause::unpause,this);
}

void State_GamePause::onDestroy(){

    EventManager *evMgr = stateMgr->getContext()->eventManager;
    evMgr->removeCallback(StateType::GamePause,"GamePause");
}

void State_GamePause::unpause(EventDetails *details){

    stateMgr->switchTo(StateType::Dungeon);
    stateMgr->remove(StateType::GamePause);
}

void State_GamePause::update(const sf::Time &time){}

void State_GamePause::draw(){

    sf::RenderWindow *wind = stateMgr->getContext()->wind->getWindow();
    wind->draw(rect);
    wind->draw(text);
}
