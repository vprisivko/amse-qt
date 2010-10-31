#include "ConsoleHandler.h"

ConsoleHandler::ConsoleHandler(Console* console){
  myconsole = console;
}

bool ConsoleHandler::startElement(const QString &, const QString &,const QString & qName, const QXmlAttributes &  atts){
  if (qName == "state") {
    myconsole->setstatetype(atts.value("statetype").toInt());
    myconsole->setballscount(atts.value("ballscount").toInt());
    myconsole->setwindowwidth(atts.value("windowwidth").toInt());
  } else {
    if (qName == "ball") {
      myconsole->setballx(atts.value("x").toInt());
      myconsole->setbally(atts.value("y").toInt());
    } else { 
      if (qName == "racket") {
        myconsole->setracketx(atts.value("x").toInt());
        myconsole->setrackethalfwidth(atts.value("halfwidth").toInt());
      } else {
        return false;
      }
    }
  }
  return true;
} 
