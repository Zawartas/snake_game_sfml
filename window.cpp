#include "window.h"
#include "inputtext.h"
#include "game.h"
#include <iostream>

Window::Window(const std::string& windowName, const sf::Vector2u& windowSize)
{
    this->mWindowName = windowName;
    this->mWindowSize = windowSize;
    this->isFullscreen = false;
    setToOpenedWindow(true);
    createWindow();
}

Window::~Window()
{
    closeWindow();
}

void Window::setToOpenedWindow(bool value) {
    isOpenedWindow = value;
}

void Window::createWindow()
{
    auto windowStyle = (isFullscreen? sf::Style::Fullscreen : sf::Style::Default);
    mWindowForRenders.create({mWindowSize.x, mWindowSize.y, 32}, mWindowName, windowStyle);
    mWindowForRenders.setFramerateLimit(30);
    mWindowForRenders.setMouseCursorVisible(false);
}

void Window::closeWindow()
{
    mWindowForRenders.close();
}

void Window::FullscreenOnOff()
{
    isFullscreen = !isFullscreen;
    closeWindow();
    createWindow();
}

void Window::startToDraw()
{
    mWindowForRenders.clear(sf::Color::Black);
}

void Window::endDrawAndShowOnScreen()
{
    mWindowForRenders.display();
}

bool Window::windowIsOpened()
{
    return isOpenedWindow;
}

bool Window::get_isFullscreen()
{
    return isFullscreen;
}

sf::RenderWindow *Window::getRenderWindow()
{
    return &mWindowForRenders;
}

sf::Vector2u Window::getWindowSize()
{
    return mWindowSize;
}

void Window::drawInWindow(sf::Drawable &v_obiekt)
{
    mWindowForRenders.draw(v_obiekt);
}


