#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

#include <SFML/Graphics.hpp>

#include "EventManager.h"

enum class StateType;

class Window{
public: // Constructor / Destructor

    Window();

    Window(const std::string &title,const sf::Vector2u& size);

    ~Window();

public: // Function

    void beginDraw(); // Clear the window

    void endDraw(); // Display the changes

    void draw(sf::Drawable &drawable);

    void update();

    bool isClose();

    bool isFullscreen();

    sf::Vector2u getWindowSize();

    void toggleFullscreen();

    bool isFocus();

    EventManager* getEventManager();

    sf::RenderWindow* getWindow();

    sf::FloatRect getViewSpace();

    void processEvents();

private: // Function

    void toggleFullscreen(EventDetails *details);

    void close(EventDetails *details = nullptr);

    void setup(const std::string &title, const sf::Vector2u &size);

    void create();

private: // Variable

    sf::RenderWindow window;

    sf::Vector2u windowSize;

    std::string windowTitle;

    bool isClosed;

    bool isFullscreens;

    EventManager eventManager;

    bool isFocused;
};

#endif
