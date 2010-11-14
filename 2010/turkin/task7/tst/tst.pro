TEMPLATE = app
TARGET = ../test
DEPENDPATH += .
INCLUDEPATH += .
QT += testlib

HEADERS += TimerDialogTest.h ../src/dialog.h
SOURCES += main.cpp TimerDialogTest.cpp ../src/dialog.cpp
