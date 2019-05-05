#include "game.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <map>
#include <algorithm>

game::game():
    mWindow("Snake", sf::Vector2u(800,600)),
    mSnake(16),
    mGameboard(sf::Vector2u(800,592), mSnake), //mniejsze bo 600 nie dzieli sie przez 16 (zostaje pasek pod dolna krawedzia
    //texts start
        userScoretext(0, 14, 110, sf::Vector2f(455,580), 1),
        userLivesLeftText(0, 14, 110, sf::Vector2f(655,580), 1),
        ESCtoExitText(0, 14, 110, sf::Vector2f(35,580), 1),
        HiScoreTableText(0, 20, 200, sf::Vector2f(300,320), 4),
        MusicOnOffText(0, 14, 110, sf::Vector2f(225,580), 1),
    //texts stop
    mObjectsToRenderOnScreen(new Object[3]{
                                        {"Objects/gameover.png", sf::Vector2f(150, 120)},
                                        {"Objects/start.png", sf::Vector2f(188, 210)},
                                        {"Objects/writeyourname.png", sf::Vector2f(20, 20)}
        }),
    mUserNameWhenGotHiScore(),
    mNameRecorded(false)
    {
        mTimeElapsed = .0f;

        //Fixed texts on screen
        userScoretext.addText("SCORE: " + std::to_string(mSnake.getScore()));
        userLivesLeftText.addText("CREDITS: " + std::to_string(getUserLives()));
        ESCtoExitText.addText("Press ESC to Exit");
        MusicOnOffText.addText("Music (Y/N)");

        //HiScoreTable setup
        HiScoreTableText.addText("HIGHSCORES:");
        HiScoreTableText.addText(openHiscoresFile("HiScore.txt"));

        //MUSIC in the background
        if (!mMusic.openFromFile("Sounds/music.wav"))
            std:: cout << "Error loading music\n";
        mMusic.play();
        mMusic.setLoop(1);
    }

game::~game()
{
    delete[] mObjectsToRenderOnScreen;
}

float game::getTimeElapsed() const
{
    return mTimeElapsed;
}

void game::receiveInput()
{
    if (getUserLives())
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
            mSnake.getCurrentDirection() != direction::DOWN)
        {
            mSnake.setDirection(direction::UP);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
                 mSnake.getCurrentDirection() != direction::UP)
        {
            mSnake.setDirection(direction::DOWN);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
                 mSnake.getCurrentDirection() != direction::LEFT)
        {
            mSnake.setDirection(direction::RIGHT);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) &&
                 mSnake.getCurrentDirection() != direction::RIGHT)
        {
            mSnake.setDirection(direction::LEFT);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::N))
        {
            toggleMusicOff();
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
        {
            toggleMusicOn();
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            mWindow.setToOpenedWindow(false);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::F5))
        {
            mWindow.FullscreenOnOff();
        }
    }
}

void game::playerLost(inputText& name)
{
    sf::Event event;
    while (mWindow.getRenderWindow()->pollEvent(event))
    {
        if (event.type == sf::Event::TextEntered)
        {
            if(event.text.unicode == '\b' && name.playerText != "")
            {
                name.playerText.erase((name.playerText).getSize() - 1, 1);
                name.playerInput.setString(name.playerText);
            }
            else if((event.text.unicode == '\b' && name.playerText == "") ||
                    event.text.unicode == 27 || event.text.unicode == 32 )
            {
            }
            else if(event.text.unicode < 128 && event.text.unicode != 13)
            {
                name.playerText += event.text.unicode;
                name.playerInput.setString(name.playerText);
            }
        }
        else if (event.type == sf::Event::KeyPressed &&
                 event.key.code == sf::Keyboard::Return)
        {
            mNameRecorded = true;
            sf::sleep(sf::seconds(1.5));
            mWindow.setToOpenedWindow(false);
        }
    }
}

bool game::isRecordHiscore()
{
    return getMinimalScoreToGetToHighscores() < getUserScore();
}

void game::update()
{
    if (getUserLives() == 0 && isRecordHiscore()) {
        playerLost(mUserNameWhenGotHiScore);
        if (mNameRecorded == true)
        {
            saveHiscoresFile("HiScore.txt", getUserScore(), getUserName());
        }
    }
    else if (getUserLives() == 0 && getMinimalScoreToGetToHighscores() >= getUserScore())
    {
        sf::sleep(sf::seconds(2));
        mWindow.setToOpenedWindow(false);
    }


    float tick_zegara = 1.0f / mSnake.getSpeed(); // e.g. 1/15

    if(mTimeElapsed >= tick_zegara)
    {
        mSnake.moveAndCheckCollisions();
        mGameboard.Update(mSnake);
        userLivesLeftText.addText("LIVES: " + std::to_string(getUserLives()));
        if (mGameboard.getAppleJustEaten())
        {
            userScoretext.addText("SCORE: " + std::to_string(mSnake.getScore()));
            mGameboard.setAppleJustEaten(false);
            mSnake.increaseSpeed(1);
        }
        mTimeElapsed -= tick_zegara;
    }
}

void game::renderGraphics()
{
    mWindow.startToDraw();

    mGameboard.render(*mWindow.getRenderWindow());
    mSnake.render(*mWindow.getRenderWindow());
    userScoretext.render(*mWindow.getRenderWindow());
    userLivesLeftText.render(*mWindow.getRenderWindow());
    ESCtoExitText.render(*mWindow.getRenderWindow());
    MusicOnOffText.render(*mWindow.getRenderWindow());

    //RENDER TYLKO na starcie
    if(mSnake.getDirection() == direction::NONE && getUserLives() == mSnake.getMaxAmountOfLives())
    {
        mObjectsToRenderOnScreen[1].render(*mWindow.getRenderWindow());
        HiScoreTableText.render(*mWindow.getRenderWindow());
    }

    //RENDER po przegranej
    if (!getUserLives())
    {
        mMusic.stop();
        mObjectsToRenderOnScreen[0].render(*mWindow.getRenderWindow());

        if (isRecordHiscore())
        {
            mObjectsToRenderOnScreen[2].render(*mWindow.getRenderWindow());
            mUserNameWhenGotHiScore.render(*mWindow.getRenderWindow());
            HiScoreTableText.changePosition(300, 380);
            HiScoreTableText.render(*mWindow.getRenderWindow());
        }
    }

    mWindow.endDrawAndShowOnScreen();
}

void game::resetTime()
{
    mTimeElapsed += mClock.restart().asSeconds();
}

Window *game::getWindow()
{
    return &mWindow;
}

std::string game::openHiscoresFile(std::string file)
{
    std::fstream stream;
    stream.open(file);
    std::string string, linia;
    int i = 0;
    while (std::getline(stream, linia) && i++ < 5)
    {
        std::istringstream linijka(linia);
        std::string temp;
        linijka >> temp;
        int score;
        linijka >> score;
        mMaxScores.push_back(score);
        std::sort(mMaxScores.begin(), mMaxScores.end());
        string = string + linia + "\n";
    }
    stream.close();
    //std::cout << "Minimum value to beat: " << getMinimalScoreToGetToHighscores() << "\n";
    return string;
}

int game::getUserLives()
{
    return mSnake.getLives();
}

std::string game::getUserName()
{
    std::string temp = mUserNameWhenGotHiScore.playerText.getSize()>8?mUserNameWhenGotHiScore.playerText.substring(0, 8):mUserNameWhenGotHiScore.playerText;
    if (temp.empty() || temp == "0")
        temp = "NoName";
    return temp;
}

int game::getUserScore()
{
    return mSnake.getScore();
}


int game::getMinimalScoreToGetToHighscores()
{
    return (!mMaxScores.empty())?mMaxScores.front():0;
}

void game::saveHiscoresFile(std::string file, int score, std::string name)
{
    //open HiScore file
    std::ifstream istream(file);
    std::multimap <int, std::string> scores;
    std::string linia;
    while (std::getline(istream, linia))
    {
        std::istringstream string(linia);
        std::string temp;
        int tempI;
        string >> temp;
        string >> tempI;
        scores.insert(std::pair<int, std::string>(tempI, temp));
    }
    scores.insert(std::pair<int, std::string>(score, name));
    istream.close();
    //closed

    std::ofstream ostream(file);
    for (std::multimap<int,std::string>::reverse_iterator it = scores.rbegin(); it != scores.rend(); ++it)
    {
        ostream << it->second << "    " << it->first << "\n";
    }
    ostream.close();
}

void game::toggleMusicOff()
{
        mMusic.stop();
}

void game::toggleMusicOn()
{
    if (!mMusic.getStatus())
    {
        mMusic.play();
        mMusic.setLoop(1);
    }
}
