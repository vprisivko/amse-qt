TEMPLATE = app
TARGET = ../test
DEPENDPATH += .
INCLUDEPATH += .
QT += testlib
# Input
HEADERS += TimerDialogTest.h ../src/dialog.h
SOURCES += main.cpp TimerDialogTest.cpp ../src/dialog.cpp
