TEMPLATE = app
DEPENDPATH += .
INCLUDEPATH += .
QT += testlib
HEADERS += TestTimerDialog.h \
    ../src/TimerDialog.h
SOURCES += TestTimerDialog.cpp \
    main.cpp \
    ../src/TimerDialog.cpp
