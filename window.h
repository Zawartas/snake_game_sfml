#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <SFML/Graphics.hpp>
#include "inputtext.h"

class inputText;
class game;

class Window { //klasa okno gry
private:
    sf::RenderWindow mWindowForRenders;
    bool isOpenedWindow;
    bool isFullscreen;
    std::string mWindowName;
    sf::Vector2u mWindowSize;
    void closeWindow();
    void createWindow();

public:
    Window() = delete;
    Window(const std::string& mWindowName, const sf::Vector2u&);
    ~Window();
    void startToDraw();
    void endDrawAndShowOnScreen();
    void setToOpenedWindow(bool value);
    bool windowIsOpened();
    bool get_isFullscreen();
    sf::RenderWindow * getRenderWindow(); //wskaznik do naszego okna 2D
    sf::Vector2u getWindowSize();
    void FullscreenOnOff();
    void drawInWindow(sf::Drawable&);

};

#endif // FUNCTIONS_H
