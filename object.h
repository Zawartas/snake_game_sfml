#ifndef OBJECT_H
#define OBJECT_H
#include <SFML/Graphics.hpp>

class Object
{
private:
    sf::Texture mTexture;
    sf::Sprite mSprite;
public:
    Object(std::string, sf::Vector2f);
    ~Object();

    void render (sf::RenderWindow &);
};

#endif // OBJECT_H
