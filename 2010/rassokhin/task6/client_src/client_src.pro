TARGET = client
TEMPLATE = app
DESTDIR = ../
QT += gui \
    core \
    network \
    xml
SOURCES += main.cpp \
    clientmainwindow.cpp \
    settingsdialog.cpp \
    clientsettings.cpp \
    clientcontrolswidget.cpp
HEADERS += clientmainwindow.h \
    settingsdialog.h \
    clientsettings.h \
    clientcontrolswidget.h \
    ../command.hpp \
    ../publicstate.hpp
