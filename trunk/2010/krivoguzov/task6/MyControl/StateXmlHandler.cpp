#include <StateXmlHandler.h>
#include <QDebug>

bool StateXmlHandler::startElement(const QString&, const QString&, const QString& qName, const QXmlAttributes& atts){

     if(qName == "DeskPosition")
        deskPosition  = atts.value(0).toInt();
     if(qName == "LifesLeft")
        lifesLeft = atts.value(0).toInt();
     if(qName == "RightBorder")
         rightBorder = atts.value(0).toInt();
     if(qName == "DeskWidth")
        deskWidth = atts.value(0).toInt();
     if(qName == "GameStatus")
        isPaused = atts.value(0).toInt();
    return true;
}

