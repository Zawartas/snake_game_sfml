#ifndef TEXTNAEKRANIE_H
#define TEXTNAEKRANIE_H
#include "SFML/Graphics.hpp"
#include <string>
#include <vector>

using MessagesContainer = std::vector<std::string>;

class TextOnScreen
{
private:
    MessagesContainer mMessages;
    int mLines;

    sf::RectangleShape mMessageBackground;
    sf::Font mFont;
    sf::Text mText;

public:
    TextOnScreen() = delete;
    TextOnScreen(int, int, int, sf::Vector2f, int);
    ~TextOnScreen();

    void setup(int, int, int, sf::Vector2f, int);
    void addText(std::string);
    void clear();
    void render(sf::RenderWindow&);
    int getLines() const;
    void changePosition(float, float);
};

#endif // TEXTNAEKRANIE_H
