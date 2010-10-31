TARGET = server
TEMPLATE = app
DESTDIR = ../
QT += core \
    gui \
    network \
    xml
SOURCES += main.cpp \
    servermainwindow.cpp \
    serversettings.cpp \
    serversettingsdialog.cpp \
    arcanoidengine.cpp \
    arcanoidviewwidget.cpp \
    ball.cpp \
    explodable.cpp \
    block.cpp \
    board.cpp
HEADERS += servermainwindow.h \
    serversettings.h \
    serversettingsdialog.h \
    arcanoidengine.h \
    ../publicstate.hpp \
    ../command.hpp \
    arcanoidviewwidget.h \
    ball.h \
    explodable.h \
    block.h \
    board.h
