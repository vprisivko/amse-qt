#ifndef STATEXMLHANDLER_H
#define STATEXMLHANDLER_H

#include <QXmlDefaultHandler>

class StateXmlHandler: public QXmlDefaultHandler {
public:
    StateXmlHandler () { deskPosition = lifesLeft = rightBorder = deskWidth = 0; isPaused = false;}
    bool startElement(const QString&, const QString&, const QString&, const QXmlAttributes&);

    int deskPosition;
    int lifesLeft;
    int rightBorder;
    int deskWidth;
    bool isPaused;

};

#endif // STATEXMLHANDLER_H
