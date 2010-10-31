#ifndef VIEWHANDLER_H
#define VIEWHANDLER_H
#include <QXmlDefaultHandler>
#include "View.h"

class ViewHandler:public QXmlDefaultHandler{
  private:
  View* myview;
  public:
  ViewHandler(View* view);
  bool startElement(const QString &, const QString &,const QString & qName, const QXmlAttributes &  ); 
};


#endif
