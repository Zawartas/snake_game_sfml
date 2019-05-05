#include "object.h"

Object::Object(std::string name, sf::Vector2f position)
{
    mTexture.loadFromFile(name);
    mSprite.setTexture(mTexture);
    mSprite.setPosition(position.x, position.y);
}

Object::~Object()
{

}

void Object::render(sf::RenderWindow &window)
{
    window.draw(mSprite);
}
