#include "Window.h"

/**************
 * Constuctor *
 **************/
Window::Window(){

    setup("Window", sf::Vector2u(1280, 720));
}

/**************
 * Constuctor *
 **************/
Window::Window(const std::string &title, const sf::Vector2u &size){

    setup(title, size);
}

/*************
 * Destuctor *
 *************/
Window::~Window(){

    window.close();
    eventManager.removeCallback("Fullscreen_toggle");
    eventManager.removeCallback("Window_close");
}

/*************
 * BeginDraw *
 *************/
void Window::beginDraw(){

    window.clear();
}

/***********
 * EndDraw *
 ***********/
void Window::endDraw(){

    window.display();
}

/**********
 * Update *
 **********/
void Window::update(){

    eventManager.update();
}

/**********
 * IsClose *
 **********/
bool Window::isClose(){

    return isClosed;
}

/****************
 * IsFullscreen *
 ****************/
bool Window::isFullscreen(){

    return isFullscreens;
}

/*****************
 * GetWindowSize *
 *****************/
sf::Vector2u Window::getWindowSize(){

    return windowSize;
}

/********************
 * ToggleFullscreen *
 ********************/
void Window::toggleFullscreen(){

    isFullscreens = !isFullscreens;
    window.close();
    create();
}

/********
 * Draw *
 ********/
void Window::draw(sf::Drawable &drawable){

    window.draw(drawable);
}

bool Window::isFocus(){

    return isFocused;
}

EventManager* Window::getEventManager(){

    return &eventManager;
}

sf::RenderWindow* Window::getWindow(){
    return &window;
}

void Window::processEvents(){

    sf::Event event;
    while (window.pollEvent(event)){

        eventManager.handleEvent(event);
    }
}

void Window::toggleFullscreen(EventDetails *details){

    isFullscreens = !isFullscreens;
    window.close();

    create();
}

/*********
 * Close *
 *********/
void Window::close(EventDetails *details){

    isClosed = true;
}

/*********
 * Setup *
 *********/
void Window::setup(const std::string &title, const sf::Vector2u &size){

    windowTitle = title;
    windowSize = size;

    isFullscreens = false;
    isClosed = false;
    isFocused = true; // Default value for focused flag.

    eventManager.addCallback("Fullscreen_toggle", &Window::toggleFullscreen, this);
    eventManager.addCallback("Window_close", &Window::close, this);

    create();
}

/**********
 * Create *
 **********/
void Window::create(){

    auto style = (isFullscreens ? sf::Style::Fullscreen : sf::Style::Default);
    window.create({windowSize.x, windowSize.y, 32}, windowTitle, style);
}