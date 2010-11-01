#include <MyXMLHandler.h>
#include <QDebug>

bool MyXmlHandler::startElement(const QString&, const QString&, const QString& qName, const QXmlAttributes& atts){

     if(qName == "Left")
        leftPressed = atts.value(0).toInt();
     if(qName == "Right")
        rightPressed = atts.value(0).toInt();
     if(qName == "GoButton")
        goPressed = atts.value(0).toInt();
     if(qName == "Pause")
        pausePressed = atts.value(0).toInt();
    return true;
}
