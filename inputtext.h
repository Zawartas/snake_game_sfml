#ifndef INPUTTEXT_H
#define INPUTTEXT_H

#include "SFML/Graphics.hpp"

class inputText
{
private:

public:
    inputText();
    ~inputText();
    sf::String playerText;
    sf::Text playerInput;
    sf::Font font;

    void render(sf::RenderWindow &);
};

#endif // INPUTTEXT_H
