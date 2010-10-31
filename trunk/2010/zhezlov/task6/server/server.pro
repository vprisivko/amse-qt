QT += network xml

TEMPLATE = app

TARGET = ../Server

HEADERS += arkanoidworld.h \
    arkanoidserver.h

SOURCES += arkanoidworld.cpp main.cpp \
    arkanoidserver.cpp
