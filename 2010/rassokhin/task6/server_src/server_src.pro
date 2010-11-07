TARGET = server
TEMPLATE = app
DESTDIR = ../
QT += core \
    gui \
    network \
    xml
SOURCES += main.cpp \
    servermainwindow.cpp \
    arcanoidengine.cpp \
    arcanoidviewwidget.cpp \
    ball.cpp \
    engineobject.cpp \
    block.cpp \
    board.cpp
HEADERS += servermainwindow.h \
    arcanoidengine.h \
    ../publicstate.hpp \
    ../command.hpp \
    arcanoidviewwidget.h \
    ball.h \
    engineobject.h \
    block.h \
    board.h
