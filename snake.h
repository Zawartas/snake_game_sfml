#ifndef SNAKE_H
#define SNAKE_H

#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>

struct SnakeSegment
{
    sf::Vector2i position;
    SnakeSegment(int x, int y):
        position(x, y) {}
};

using SnakeContainer = std::vector<SnakeSegment>;

enum class direction {NONE, UP, DOWN, LEFT, RIGHT};

class Snake
{
private:
    SnakeContainer mSnakeBody;
    direction mDirection;
    int mSpeed;
    int mLives;
    int mScore;
    bool mLost;
    int mMaxAmountOfLives = 5;

    sf::RectangleShape mSquare;
    int mSegmentSize;
    void checkCollisionWithItself();

    sf::SoundBuffer mBuffer;
    sf::Sound mSound;

public:
    Snake(int);

    sf::Vector2i getPosition();

    void increaseScore();

    void gameOver();
    void switchPrzegrana();

    void makeLonger();
    void reset();

    void move();
    void moveAndCheckCollisions();
    void cutSnake (int);
    void decreaseLives();

    void render (sf::RenderWindow &);
    direction getDirection() const;
    direction getCurrentDirection();
    void setDirection(const direction &);
    int getSpeed() const;
    int getLives() const;
    int getScore() const;
    bool getLostState() const;
    int getSnakeLength() const;

    void increaseSpeed(int value);
    int getMaxAmountOfLives() const;
    SnakeContainer getCialkoWeza() const;
};

#endif // SNAKE_H
