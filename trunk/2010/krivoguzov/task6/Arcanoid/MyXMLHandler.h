#ifndef MYXMLHANDLER_H
#define MYXMLHANDLER_H

#include <QXmlDefaultHandler>

class MyXmlHandler: public QXmlDefaultHandler {
public:
    MyXmlHandler () {leftPressed = rightPressed = goPressed = pausePressed = false; }
    bool startElement(const QString&, const QString&, const QString&, const QXmlAttributes&);

    bool leftPressed;
    bool rightPressed;
    bool goPressed;
    bool pausePressed;

};

#endif // MYXMLHANDLER_H
