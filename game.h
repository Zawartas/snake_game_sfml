#ifndef GRA_H
#define GRA_H
#include "window.h"
#include "board.h"
#include "snake.h"
#include "textonscreen.h"
#include "object.h"

#include <SFML/Audio.hpp>
#include <vector>

class game
{
private:
    Window mWindow;
    Snake mSnake;
    Plansza mGameboard;

    TextOnScreen userScoretext;
    TextOnScreen userLivesLeftText;
    TextOnScreen ESCtoExitText;
    TextOnScreen HiScoreTableText;
    TextOnScreen MusicOnOffText;

    Object* mObjectsToRenderOnScreen;
    sf::Clock mClock;
    sf::Music mMusic;

    float mTimeElapsed;
    inputText mUserNameWhenGotHiScore;
    bool mNameRecorded;
    std::vector <int> mMaxScores;

public:
    game();
    ~game();

    //main functions
    void receiveInput();
    void update();
    void renderGraphics();
    void resetTime();

    //getters
    Window *getWindow();
    float getTimeElapsed() const;
    int getUserLives();
    std::string getUserName();
    int getUserScore();
    int getMinimalScoreToGetToHighscores();

    //end game functions
    void playerLost(inputText&);
    bool isRecordHiscore();
    std::string openHiscoresFile(std::string);
    void saveHiscoresFile(std::string, int, std::string);

    void toggleMusicOn();
    void toggleMusicOff();
};

#endif // GRA_H
