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
}

/*********
 * Setup *
 *********/
void Window::setup(const std::string title, const sf::Vector2u &size)
{
    windowTitle = title;
    windowSize = size;
    isFullscreen = false;
    isClose = false;
    create();
}

/**********
 * Create *
 **********/
void Window::create(){

    auto style = (m_isFullscreen ? sf::Style::Fullscreen : sf::Style::Default);
    window.create({windowSize.x, windowSize.y, 32}, windowTitle, style);
}

/**********
 * Update *
 **********/
void Window::update(){

    sf::Event event;

    while(window.pollEvent(event)){

        if(event.type == sf::Event::Closed)
            isClose = true;

        else if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F5);
            toggleFullscreen();

    }
}

/********************
 * ToggleFullscreen *
 ********************/
void Window::toggleFullscreen(){

    isFullscreen = !isFullscreen;
    window.close();
    create();
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
 * IsClose *
 **********/
bool Window::isClose(){
    return isClose;
}

/****************
 * IsFullscreen *
 ****************/
bool Window::isFullscreen(){
    return isFullscreen;
}

/*****************
 * GetWindowSize *
 *****************/
sf::Vector2u Window::getWindowSize(){
    return windowSize;
}

/********
 * Draw *
 ********/
void Window::draw(sf::Drawable &drawable){
    window.draw(drawable);
}

