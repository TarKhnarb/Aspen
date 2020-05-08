#ifndef GAME_EVENTMANAGER_H
#define GAME_EVENTMANAGER_H

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Vector2.hpp>

#include <vector>
#include <unordered_map>
#include <functional>
#include <fstream>
#include <sstream>
#include <iostream>

enum class EventType{

    Closed = sf::Event::Closed,
    KeyDown = sf::Event::KeyPressed,
    KeyUp = sf::Event::KeyReleased,
    WindowResized = sf::Event::Resized, // A voir si utile pour les options (fullscreen ou pas)
    GainedFocus = sf::Event::GainedFocus, // A voir si utile pour Map
    LostFocus = sf::Event::LostFocus, // A voir si utile pour Map
    Keyboard = sf::Event::Count + 1
};

/* List of different events
 *
 * KeyDown = sf::Event::KeyPressed,
 * KeyUp = sf::Event::KeyReleased,
 * MButtonDown = sf::Event::MouseButtonPressed,
 * MButtonUp = sf::Event::MouseButtonReleased,
 * MouseWheel = sf::Event::MouseWheelMoved,
 * WindowResized = sf::Event::Resized,
 * GainedFocus = sf::Event::GainedFocus,
 * LostFocus = sf::Event::LostFocus,
 * MouseEntered = sf::Event::MouseEntered,
 * MouseLeft = sf::Event::MouseLeft,
 * Closed = sf::Event::Closed,
 * TextEntered = sf::Event::TextEntered,
 * Keyboard = sf::Event::Count + 1, Mouse, Joystick
 */

struct EventInfo{

    EventInfo(){

        code = 0;
    }

    EventInfo(int event){

        code = event;
    }


    union{

        int code;
    }; //  A voir si utile
};

struct EventDetails{

    EventDetails(const std::string &bindName):
            name(bindName){

        clear();
    }
    std::string name;
    sf::Vector2i size;
    sf::Uint32 textEntered;
    int keyCode; // Single key code.

    void clear(){

        size = sf::Vector2i(0, 0);
        textEntered = 0;
        keyCode = -1;
    }
};

using Events = std::vector<std::pair<EventType, EventInfo>>;

struct Binding{

    Binding(const std::string &name):
            name(name),
            count(0),
            details(name){}

    void bindEvent(EventType type, EventInfo info = EventInfo()){

        events.emplace_back(type, info);
    }

    Events events;
    std::string name;
    std::size_t count; // Count of events that are "happening".
    EventDetails details;
};

using Bindings = std::unordered_map<std::string, Binding*>;

using Callbacks = std::unordered_map<std::string, std::function<void(EventDetails*)>>;

class EventManager{

public:

    EventManager();
    ~EventManager();

public:

    bool addBinding(Binding *binding);
    bool removeBinding(std::string name);
    void setFocus(const bool &focus);
// Needs to be defined in the header!
    template<class T>
    bool addCallback(const std::string &name, void(T::*func)(EventDetails*), T* instance){

        auto temp = std::bind(func, instance, std::placeholders::_1);
        return callbacks.emplace(name, temp).second;
    }

    void removeCallback(const std::string& name){
        callbacks.erase(name);
    }

    void handleEvent(sf::Event &event);

    void update();

private:

    void loadBindings();
    Bindings bindings;
    Callbacks callbacks;
    bool hasFocus;
};

#endif