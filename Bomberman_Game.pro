TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    Bomberman/Collision.cpp \
        Bomberman/background.cpp \
        Bomberman/bomberman.cpp \
        Bomberman/sprites.cpp \
        Game/Game.cpp \
        Game/GameText.cpp \
        Game/Thumbnail.cpp \
        main.cpp \

LIBS += -LC:\SFML-2.5.1\lib
LIBS += -LC:\SFML-2.5.1\bin

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-network -lsfml-window
CONFIG(debug  , debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-network -lsfml-window

INCLUDEPATH += C:\SFML-2.5.1\include
DEPENDPATH += C:\SFML-2.5.1\include

HEADERS += \
    Bomberman/Collision.h \
    Bomberman/background.h \
    Bomberman/bomberman.h \
    Bomberman/sprites.h \
    Game.h \
    Game/Game.h \
    Game/GameText.h \
    Game/Thumbnail.h \
