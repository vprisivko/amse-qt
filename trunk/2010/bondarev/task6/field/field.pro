TARGET = ../fieldForGame
TEMPLATE = app
DEPENDPATH += .
INCLUDEPATH += .
QT += network \
    xml
HEADERS += arcanoid.h
SOURCES += main.cpp \
    arcanoid.cpp
