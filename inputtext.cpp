#include "inputtext.h"
#include <iostream>

inputText::inputText()
{

    if(!font.loadFromFile("Fonts/FFFFORWA.ttf"))
        std::cout << "Can't loadt font!\n";
    playerInput.setFont(font);
    playerInput.setPosition(sf::Vector2f(450,45));
    playerInput.setFillColor(sf::Color::White);
    playerInput.setCharacterSize(24);
    playerInput.setStyle(sf::Text::Bold | sf::Text::Underlined);
}

inputText::~inputText()
{

}

void inputText::render(sf::RenderWindow &okno)
{
    okno.draw(playerInput);
}
