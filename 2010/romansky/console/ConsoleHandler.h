#ifndef CONSOLEGANDLER_H
#define CONSOLEHANDLER_H
#include <QXmlDefaultHandler>
#include "Console.h"

class ConsoleHandler:public QXmlDefaultHandler{
  private:
  Console* myconsole;
  public:
  ConsoleHandler(Console* console);
  bool startElement(const QString &, const QString &,const QString & qName, const QXmlAttributes &  atts); 
};

#endif
