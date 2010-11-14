#include "myParser.h"


bool myParser::startElement(const QString &, 
                    const QString &, 
                    const QString &qName, 
                    const QXmlAttributes &attribs){
  if (qName =="state"){
    attr.gameover = attribs.value("gameover").toInt();
    attr.isStarted = attribs.value("isStarted").toInt();
    attr.left = attribs.value("left").toInt();
    attr.right = attribs.value("right").toInt();
  }
  return true;
    
};
