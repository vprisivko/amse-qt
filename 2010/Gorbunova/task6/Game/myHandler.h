#ifndef _MYHANDLER_
#define _MYHANDLER_
#include <QPushButton>
#include <QXmlReader>
#include <QHostAddress>
#include <QDomDocument>
#include "attributs.h"
class myHandler: public QXmlDefaultHandler {
  public:
    bool startElement(const QString &, const QString &, const QString & name, const QXmlAttributes & attrs);
    myattributs attr;
};


#endif
