TEMPLATE = app
TARGET = ../test
DEPENDPATH += .
INCLUDEPATH += .
QT += testlib
# Input
HEADERS += TimerTest.h ../src/dialog.h
SOURCES += main.cpp TimerTest.cpp ../src/dialog.cpp
