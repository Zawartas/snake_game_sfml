#include "textonscreen.h"
#include <string>
#include <fstream>

TextOnScreen::TextOnScreen(int a, int b, int c, sf::Vector2f d, int e)
{
    setup(a, b, c, d, e);
}

TextOnScreen::~TextOnScreen()
{
    clear();
}

void TextOnScreen::setup(int size, int fontSize, int width, sf::Vector2f position, int lines)
{
    this->mLines = lines;
    sf::Vector2f offset (2.0f, 0.0f);

    mFont.loadFromFile("Fonts/FFFFORWA.ttf");

    mText.setFont(mFont);
    mText.setString("");
    mText.setCharacterSize(fontSize);
    mText.setColor(sf::Color::White);
    mText.setPosition(position + offset);

    mMessageBackground.setSize(sf::Vector2f(width, (size * (fontSize * 1.2f))));
    mMessageBackground.setFillColor(sf::Color(90,90,90,90));
    mMessageBackground.setPosition(position);
}

int TextOnScreen::getLines() const
{
    return mLines;
}

void TextOnScreen::changePosition(float x, float y)
{
    mText.setPosition(sf::Vector2f(x, y));
}

void TextOnScreen::addText(std::string message)
{
    mMessages.push_back(message);
    if(mMessages.size() <= (unsigned)getLines())
    {
        return;
    }
    mMessages.erase(mMessages.begin());
}

void TextOnScreen::clear()
{
    mMessages.clear();
}

void TextOnScreen::render(sf::RenderWindow &window)
{
    std::string message;

    for(auto &itr : mMessages)
    {
        message.append(itr + "\n");
    }
    if (message != "")
    {
        mText.setString(message);
        window.draw(mMessageBackground);
        window.draw(mText);
    }
}
