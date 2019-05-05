#include "board.h"
#include <iostream>
#include <cstdlib>

extern int k;

Plansza::Plansza(sf::Vector2u rozmiarOkna, Snake &snake):
    mWindowSize(rozmiarOkna),
    mGridSize(16)
{
    createApple(snake);
    mCircle.setFillColor(sf::Color::Red);
    mCircle.setRadius(mGridSize/2);

    for (int i = 0; i < 4; ++i)
    {
        mBorders[i].setFillColor(sf::Color(150,0,0));
        //SIZE
        if (i == 0 || i == 2)
            mBorders[i].setSize(sf::Vector2f(rozmiarOkna.x, mGridSize));
        else
            mBorders[i].setSize(sf::Vector2f(mGridSize, rozmiarOkna.y));
        //PLACE
        if (i < 2) // 0 i 1 |-
        {
            mBorders[i].setPosition(0,0);
        }
        else // 2 i 3 _|
        {
            mBorders[i].setOrigin(mBorders[i].getSize()); //eg (16,800) bottom right corner
            mBorders[i].setPosition(sf::Vector2f(rozmiarOkna)); //that corner from above
                                                              //is placed it bottom left corner of our window
        }
    }

    if (!mBuffer.loadFromFile("Sounds/apple.wav"))
        std::cout << "Can't load Apple eaten sound!\n";
    mAppleEatenSound.setBuffer(mBuffer);
    srand(static_cast<unsigned>(time(nullptr)));
}

int Plansza::getSizeGrid() const
{
    return mGridSize;
}

void Plansza::createApple(Snake &snake)
{
    bool appleCreated = false;
    while (appleCreated == false)
    {
        int maxX = (mWindowSize.x/mGridSize) - 2;
        int maxY = (mWindowSize.y/mGridSize) - 2;
        mApple = sf::Vector2i(rand()%maxX + 1, rand()%maxY + 1);

        if (mObstacles.size() > 0)
        {
            for(auto it = mObstacles.begin(); it != mObstacles.end(); ++it)
            {
                if (mApple.x >= it->getPosition().x/mGridSize &&
                    mApple.x < (it->getPosition().x+it->getSize().x)/mGridSize &&
                    mApple.y >= it->getPosition().y/mGridSize &&
                    mApple.y < (it->getPosition().y+it->getSize().y)/mGridSize)
                {
                    appleCreated = false;
                    break;
                }
                else
                    appleCreated = true;
            }
        }
        if (!mObstacles.size())
            appleCreated = true;

        if (appleCreated)
        {
            for (int i = 0; i < snake.getCialkoWeza().size(); ++i)
            {
                if (mApple.x == snake.getCialkoWeza().at(i).position.x &&
                    mApple.y == snake.getCialkoWeza().at(i).position.y)
                {
                    appleCreated = false;
                    break;
                }
                else {
                    mCircle.setPosition(sf::Vector2f(mApple.x*mGridSize, mApple.y*mGridSize));
                }
            }
        }
    }
}

bool Plansza::getAppleJustEaten() const
{
    return isAppleJustEaten;
}

void Plansza::setAppleJustEaten(bool value)
{
    isAppleJustEaten = value;
}

void Plansza::Update(Snake &snake)
{
    if(snake.getPosition() == mApple)
    {
        mAppleEatenSound.play();
        setAppleJustEaten(true);
        snake.makeLonger();
        snake.increaseScore();
        for (int i = 0; i < 2; i++)
            addObstacle(snake);
        createApple(snake);

    }

    int planszaRozmiarX = mWindowSize.x/mGridSize;
    int planszaRozmiarY = mWindowSize.y/mGridSize;

    if( snake.getPosition().x <= 0 ||
        snake.getPosition().y <= 0 ||
        snake.getPosition().x >= planszaRozmiarX - 1 ||
        snake.getPosition().y >= planszaRozmiarY - 1)
    {
        snake.decreaseLives();
        snake.reset();
    }

    for(auto it = mObstacles.begin(); it != mObstacles.end(); ++it)
    {
        if (snake.getPosition().x >= it->getPosition().x/mGridSize &&
            snake.getPosition().x < (it->getPosition().x+it->getSize().x)/mGridSize &&
            snake.getPosition().y >= it->getPosition().y/mGridSize &&
            snake.getPosition().y < (it->getPosition().y+it->getSize().y)/mGridSize)
        {
            snake.decreaseLives();
            snake.reset();
        }
    }
}

void Plansza::render(sf::RenderWindow &okno)
{
    okno.draw(mCircle);
    for (auto it: mObstacles)
    {
        okno.draw(it);
    }
    for (auto & it: mBorders)
        okno.draw(it);
}

void Plansza::addObstacle(Snake &snake)
{ 
    sf::RectangleShape object;

        int x_siz_rand = rand()%6 + 2;
        int y_siz_rand = rand()%6 + 2;

    object.setFillColor(sf::Color(rand()%256+40,rand()%256+40,rand()%256+40));
    object.setSize(sf::Vector2f(mGridSize * x_siz_rand, mGridSize * y_siz_rand));

        int x_position;
        int y_position;
    do
    {
        do
        {
            x_position = rand()%49-x_siz_rand+1;
        }
        while (x_position <= 0);

        do
        {
            y_position = rand()%36-y_siz_rand+1;
        }
        while (y_position <= 0);
    }
    while (isColisionSnakeWithObject(snake, x_position, y_position, x_position+x_siz_rand-1, y_position+y_siz_rand-1));

    object.setPosition(mGridSize * x_position, mGridSize * y_position);

    mObstacles.push_back(object);
}

bool Plansza::isColisionSnakeWithObject(Snake &snake, int x1, int y1, int x2, int y2)
{
    if (3 >= x1 && 3 <= x2 && y2 < 20)
        return true;

    auto cialkoWeza = snake.getCialkoWeza();
    for (auto it = cialkoWeza.begin(); it != cialkoWeza.end(); ++it)
    {
        if(it->position.x >= x1 && it->position.x <= x2 &&
           it->position.y >= y1 && it->position.y <= y2)
        {
            return true;
        }
    }
    return false;
}
