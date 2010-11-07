TEMPLATE = subdirs
TARGET =
DEPENDPATH += . Controller PlayGround
#INCLUDEPATH += . Controller PlayGround

# Input
#HEADERS += Controller/ControlDialog.h PlayGround/ArcanoidDialog.h PlayGround/BallAndRocket.h
#SOURCES += Controller/main.cpp Controller/ControlDialog.cpp PlayGround/main.cpp PlayGround/ArcanoidDialog.cpp PlayGround/BallAndRocket.cpp
SUBDIRS += Controller PlayGround
