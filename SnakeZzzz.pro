TEMPLATE = app
CONFIG += c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    snake.cpp \
    window.cpp \
    object.cpp \
    inputtext.cpp \
    game.cpp \
    textonscreen.cpp \
    board.cpp

LIBS += -LC:\SFML\lib #path to dll's

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-main -lsfml-network -lsfml-window -lsfml-system

INCLUDEPATH += C:\SFML\include

HEADERS += \
    snake.h \
    window.h \
    object.h \
    inputtext.h \
    game.h \
    textonscreen.h \
    board.h
