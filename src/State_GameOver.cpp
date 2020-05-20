#include "State_GameOver.h"
#include "StateManager.h"

State_GameOver::State_GameOver(StateManager *stateMgr):
        BaseState(stateMgr),
        Aspen(*stateMgr->getContext()->aspen){}

State_GameOver::~State_GameOver(){}

void State_GameOver::onCreate(){

    timePassed = 0.0f;

    sf::Vector2u windowSize = stateMgr->getContext()->wind->getWindow()->getSize();

    font.loadFromFile("Data/Fonts/Verdana.ttf");
    text.setFont(font);
    text.setString({"Press SPACE to continue"});
    text.setCharacterSize(15);
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    text.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);

    comment.setFont(font);
    if(Aspen.getStats()->getFinalValue(StatName::Life) <= 0.f)
        comment.setString({"GAME OVER you will do better next time"});
    else
        comment.setString({"Congratulations you have finished the dungeon"});

    comment.setCharacterSize(25);
    sf::FloatRect commentRect = comment.getLocalBounds();
    comment.setOrigin(commentRect.left + commentRect.width / 2.0f, commentRect.top + commentRect.height / 2.0f);
    comment.setPosition((windowSize.x / 2.0f), (windowSize.y / 2.0f) - 2.f * textRect.height);

    EventManager *evMgr = stateMgr->getContext()->eventManager;
    evMgr->addCallback(StateType::GameOver, "Valid", &State_GameOver::continu,this);
}

void State_GameOver::onDestroy(){

    EventManager *evMgr = stateMgr->getContext()->eventManager;
    evMgr->removeCallback(StateType::GameOver,"GameOver_Continue");
}

/***********
 * Continu *
 ***********/
void State_GameOver::continu(EventDetails *details){

    if(timePassed >= 2.f){

        stateMgr->switchTo(StateType::Map);
        stateMgr->remove(StateType::GameOver);
    }
}

void State_GameOver::update(const sf::Time &time){

    if(timePassed < 2.f)
        timePassed += time.asSeconds();
}

void State_GameOver::draw(){

    sf::RenderWindow *window = stateMgr->getContext()->wind->getWindow();

    if(timePassed >= 2.f){
        window->draw(comment);
        window->draw(text);
    }
}