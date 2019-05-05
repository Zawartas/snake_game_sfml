#include "game.h"
//#include <SFML/Window.hpp>

//#include <iostream>

int main(){

    game GAME;

    //system("dir");
    //std::cout << "compiler version: " << __GNUC__ << "." << __GNUC_MINOR__ << " " << __GNUC_PATCHLEVEL__ << std::endl;

    while (GAME.getWindow()->windowIsOpened())
    {
        GAME.receiveInput();
        GAME.update();
        GAME.renderGraphics();
        GAME.resetTime();
    }

return 0;
}
