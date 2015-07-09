#-------------------------------------------------
#
# Project created by QtCreator 2015-05-15T21:58:37
#
#-------------------------------------------------

QT +=  opengl multimedia gui
CONFIG+=c++11
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


SOURCES += main.cpp\
    gamemanager.cpp \
    player.cpp \
    gameobject.cpp \
    maze.cpp \
    wall.cpp \
    floor.cpp \
    sky.cpp \
    goal.cpp \
    hudmanager.cpp \
    mediaplayermanager.cpp \
    model.cpp \
    goomba.cpp \
    enemymanager.cpp \
    fireball.cpp

HEADERS  += gamemanager.h \
    player.h \
    gameobject.h \
    maze.h \
    wall.h \
    floor.h \
    sky.h \
    goal.h \
    hudmanager.h \
    mediaplayermanager.h \
    model.h \
    goomba.h \
    enemymanager.h \
    fireball.h

LIBS+=-lglut -lGLU -lgle -lftgl


DISTFILES += \
    matrix.txt \
    draw.txt
INCLUDEPATH += "/usr/include/freetype2"
