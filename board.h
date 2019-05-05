#ifndef Plansza_H
#define Plansza_H

#include "snake.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

class Plansza
{
private:
    sf::Vector2u mWindowSize;
    sf::Vector2i mApple;
    int mGridSize;
    bool isAppleJustEaten = false;
    bool isObstacleCreated = false;

    sf::CircleShape mCircle;
    sf::RectangleShape mBorders[4];
    std::vector <sf::RectangleShape> mObstacles;

    sf::SoundBuffer mBuffer;
    sf::Sound mAppleEatenSound;

public:
    Plansza(sf::Vector2u, Snake &snake);

    int getSizeGrid() const;
    void createApple(Snake &snake);

    void Update (Snake&);
    void render (sf::RenderWindow &);
    bool getAppleJustEaten() const;
    void setAppleJustEaten(bool value);
    void addObstacle(Snake&);
    bool isColisionSnakeWithObject(Snake&, int, int, int, int);
};

#endif // Plansza_H
