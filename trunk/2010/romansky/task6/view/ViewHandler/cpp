#include "ViewHandler.h"
ViewHandler::ViewHandler(View* view){
  myview = view;
}

bool ViewHandler::startElement(const QString &, const QString &,const QString & qName, const QXmlAttributes & ){
  if (myview == NULL) {
    return false;
  }

  if (qName == "right"){
    myview->moveRacketRight();
  } else {
    if (qName == "left"){
      myview->moveRacketLeft();
    } else {
      if (qName == "stop"){
        myview->stop();
        myview->setState(myview->NOTSTARTED);
      } else {
        if (qName == "start"){
          myview->start();
          myview->setState(myview->STARTED);
        }  else {
          return false;
        }
      }
    }
  }
  return true;
} 
