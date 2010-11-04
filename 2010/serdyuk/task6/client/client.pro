QT += network xml

SOURCES = main.cpp \
          widget.cpp \
          ../server/state.cpp \
          ../server/ball.cpp \
          ../server/racket.cpp \
          ../server/statehandler.cpp

HEADERS = widget.h \
          ../server/state.h \
          ../server/ball.h \
          ../server/racket.h \
          ../server/statehandler.h

TARGET = ../clientapp
