TEMPLATE = app
TARGET = ../task7
DEPENDPATH += .
INCLUDEPATH += .
QT += testlib

# Input
HEADERS += testtimers.h ../src/timers.h
SOURCES += main.cpp testtimers.cpp ../src/timers.cpp
