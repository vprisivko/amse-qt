TEMPLATE = app
TARGET = ../task7
DEPENDPATH += .
INCLUDEPATH += .
QT += testlib

# Input
HEADERS += tst.h ../src/src.h
SOURCES += main.cpp tst.cpp ../src/src.cpp
