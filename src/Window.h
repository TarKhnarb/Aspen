#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

#include <SFML/Graphics.hpp>

class Window{
public: // Constructor / Destructor
    Window();
    Window(const std::string &title,const sf::Vector2u& size);

    ~Window();

public: // Function

    void beginDraw(); // Clear the window.
    void endDraw(); // Display the changes.
    void update();
    bool isClose();
    bool isFullscreen();
    sf::Vector2u getWindowSize();
    void toggleFullscreen();
    void draw(sf::Drawable &drawable);

private: // Function

    void setup(const std::string &title, const sf::Vector2u &size);
    void create();

private: // Variable

    sf::RenderWindow window;
    sf::Vector2u windowSize;
    std::string windowTitle;

    bool isClose;
    bool isFullscreen;
};

#endif