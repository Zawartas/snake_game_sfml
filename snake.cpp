#include "snake.h"

#include <fstream>
#include <sstream>
#include <SFML/Audio.hpp>



Snake::Snake(int segmentSize)
{
    this->mSegmentSize = segmentSize;
    mSquare.setSize(sf::Vector2f(segmentSize-1, segmentSize-1));
    mLives = getMaxAmountOfLives();
    mScore = 0;
    mSpeed = 10;
    reset();
}

direction Snake::getDirection() const
{
    return mDirection;
}

direction Snake::getCurrentDirection()
{
    if(getSnakeLength() <= 1)
        return direction::NONE;

    SnakeSegment &head = mSnakeBody[0];
    SnakeSegment &beforeHead = mSnakeBody[1];

    if(head.position.x == beforeHead.position.x)
        return head.position.y > beforeHead.position.y?direction::DOWN:direction::UP;
    else if(head.position.y == beforeHead.position.y)
        return head.position.x > beforeHead.position.x?direction::RIGHT:direction::LEFT;

    return direction::NONE;
}

void Snake::setDirection(const direction &value)
{
    mDirection = value;
}

int Snake::getSpeed() const
{
    return mSpeed;
}

int Snake::getLives() const
{
    return mLives;
}

int Snake::getScore() const
{
    return mScore;
}

bool Snake::getLostState() const
{
    return mLost;
}

int Snake::getSnakeLength() const
{
    return mSnakeBody.size();
}

void Snake::increaseSpeed(int value)
{
    mSpeed += value;
}

int Snake::getMaxAmountOfLives() const
{
    return mMaxAmountOfLives;
}

SnakeContainer Snake::getCialkoWeza() const
{
    return mSnakeBody;
}

void Snake::checkCollisionWithItself()
{
    if (getSnakeLength() < 5) return;
    SnakeSegment &glowa = mSnakeBody.front();
    for (auto it = mSnakeBody.begin()+1; it != mSnakeBody.end(); ++it)
    {
        if(it->position == glowa.position)
        {
            int placeToCut = mSnakeBody.end() - it;
            cutSnake(placeToCut);
            break;
        }
    }
}

sf::Vector2i Snake::getPosition()
{
    return !mSnakeBody.empty()?mSnakeBody.front().position:sf::Vector2i(1,1);
}

void Snake::increaseScore()
{
    mScore += 10;
}

void Snake::gameOver()
{
    mLost = true;

    getScore();
    setDirection(direction::NONE);
    reset();
}

void Snake::switchPrzegrana()
{
    mLost = !mLost;
}

void Snake::makeLonger()
{
    if (mSnakeBody.empty()) return;
    SnakeSegment &ogon = mSnakeBody[getSnakeLength() - 1];

    if (getSnakeLength() > 1)
    {
            SnakeSegment &przed_ogon = mSnakeBody[getSnakeLength() - 2];
            if(ogon.position.x == przed_ogon.position.x)
            {
                if(ogon.position.y > przed_ogon.position.y)
                {
                    mSnakeBody.push_back(SnakeSegment(ogon.position.x, ogon.position.y + 1));
                }
                else
                    mSnakeBody.push_back(SnakeSegment(ogon.position.x, ogon.position.y - 1));
            }
            else if (ogon.position.y == przed_ogon.position.y)
            {
                if(ogon.position.x > przed_ogon.position.x)
                {
                    mSnakeBody.push_back(SnakeSegment(ogon.position.x + 1, ogon.position.y));
                }
                else
                    mSnakeBody.push_back(SnakeSegment(ogon.position.x - 1, ogon.position.y));
            }
    }
    else
    {
        if(mDirection == direction::UP)
            mSnakeBody.push_back(SnakeSegment(ogon.position.x, ogon.position.y + 1));
        else if (mDirection == direction::DOWN)
        {
            mSnakeBody.push_back(SnakeSegment(ogon.position.x, ogon.position.y - 1));
        }
        else if (mDirection == direction::LEFT)
        {
            mSnakeBody.push_back(SnakeSegment(ogon.position.x + 1, ogon.position.y));
        }
        else if (mDirection == direction::RIGHT)
        {
            mSnakeBody.push_back(SnakeSegment(ogon.position.x - 1, ogon.position.y));
        }
    }
}

void Snake::reset() //waz 'od nowa' / 'nowa gra'
{
    mSnakeBody.clear();
    mSnakeBody.push_back(SnakeSegment(3,5));
    mSnakeBody.push_back(SnakeSegment(3,4));
    mSnakeBody.push_back(SnakeSegment(3,3));

    setDirection(direction::NONE);
}

void Snake::move()
{
    for (int i = getSnakeLength() - 1; i > 0; --i)
        mSnakeBody[i].position = mSnakeBody[i-1].position;
    if (mDirection == direction::LEFT)
        --mSnakeBody[0].position.x;
    if (mDirection == direction::RIGHT)
        ++mSnakeBody[0].position.x;
    if (mDirection == direction::DOWN)
        ++mSnakeBody[0].position.y;
    if (mDirection == direction::UP)
        --mSnakeBody[0].position.y;

    //std::cout << "Snake position: " << getPosition().x << " " << getPosition().y << std::endl;
}

void Snake::moveAndCheckCollisions()
{
    if (mSnakeBody.empty()) {return;}
    if (mDirection == direction::NONE) return;
    move();
    checkCollisionWithItself();
}

void Snake::cutSnake(int x)
{
    for (int i = 0; i < x; i++)
        mSnakeBody.pop_back();
    decreaseLives();
}

void Snake::decreaseLives()
{
    --mLives;
    if (!mBuffer.loadFromFile("Sounds/wall.wav"))
        std::cout << "error loading sound in " << __func__ << std::endl;

    mSound.setBuffer(mBuffer);
    mSound.setVolume(18);
    mSound.play();

    if (!mLives)
    {
        gameOver();
        return;
    }
}

void Snake::render(sf::RenderWindow &okno)
{
    if(mSnakeBody.empty()) return;

    auto head = mSnakeBody.begin();
    mSquare.setFillColor(sf::Color::Yellow);
    mSquare.setPosition(head->position.x * mSegmentSize,
                          head->position.y * mSegmentSize);
    okno.draw(mSquare);

    mSquare.setFillColor(sf::Color::Green);
    for (auto it = mSnakeBody.begin()+1; it != mSnakeBody.end();++it)
    {
        mSquare.setPosition(it->position.x * mSegmentSize,
                              it->position.y * mSegmentSize);
        okno.draw(mSquare);
    }
}



