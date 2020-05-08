#include "EventManager.h"

EventManager::EventManager():
        hasFocus(true){
    loadBindings();
}

EventManager::~EventManager(){

    for(auto &itr : bindings){

        delete itr.second;
        itr.second = nullptr;
    }
}

bool EventManager::addBinding(Binding *binding){

    if(bindings.find(binding->name) != bindings.end())
        return false;
    return bindings.emplace(binding->name, binding).second;
}

bool EventManager::removeBinding(std::string name){

    auto itr = bindings.find(name);
    if (itr == bindings.end()){
        return false;
    }
    delete itr->second;
    bindings.erase(itr);
    return true;
}

void EventManager::handleEvent(sf::Event &event){

    for(auto &b_itr : bindings){

        Binding *bind = b_itr.second;
        for(auto &e_itr : bind->events){

            EventType sfmlEvent = (EventType)event.type;
            if(e_itr.first != sfmlEvent)
                continue;

            if(sfmlEvent == EventType::KeyDown || sfmlEvent == EventType::KeyUp){

                if(e_itr.second.code == event.key.code){

                    if (bind->details.keyCode != -1)
                        bind->details.keyCode = e_itr.second.code;

                    ++(bind->count);
                    break;
                }
            }
            else
                ++(bind->count);

        }
    }
}

void EventManager::update(){

    if(!hasFocus)
        return;

    for(auto &b_itr : bindings){

        Binding* bind = b_itr.second;
        for(auto &e_itr : bind->events){

            switch (e_itr.first){

                case(EventType::Keyboard):

                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(e_itr.second.code))){

                        if(bind->details.keyCode == -1)
                            bind->details.keyCode = e_itr.second.code;

                        ++(bind->count);
                    }
                    break;

                default:
                    break;
            }
        }
        if(bind->events.size() == bind->count){

            auto callItr = callbacks.find(bind->name);
            if(callItr != callbacks.end())
                callItr->second(&bind->details);

        }
        bind->count = 0;
        bind->details.clear();
    }
}

void EventManager::loadBindings(){

    std::string delimiter = ":";
    std::ifstream bind;
    bind.open("Data/Files/EventManager/keys.cfg");

    if(!bind.is_open()){

        std::cout << "! Failed loading keys.cfg." << std::endl;
        return;
    }
    std::string line;

    while(std::getline(bind, line)){

        std::stringstream keystream(line);
        std::string callbackName;
        keystream >> callbackName;
        Binding *bind = new Binding(callbackName);

        while(!keystream.eof()){

            std::string keyval;
            keystream >> keyval;
            int start = 0;
            std::size_t end = keyval.find(delimiter);

            if (end == std::string::npos){

                delete bind;
                bind = nullptr;
                break;
            }

            EventType type = EventType(stoi(keyval.substr(start, end - start)));
            int code = stoi(keyval.substr(end + delimiter.length(), keyval.find(delimiter, end + delimiter.length())));
            EventInfo eventInfo;
            eventInfo.code = code;
            bind->bindEvent(type, eventInfo);
        }
        if (!addBinding(bind))
            delete bind;

        bind = nullptr;
    }
    bind.close();
}

