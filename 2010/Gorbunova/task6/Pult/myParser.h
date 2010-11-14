#ifndef _MYPARSER_
#define _MYPARSER_
#include <QXmlDefaultHandler>
#include "controlattributs.h"

class myParser: public QXmlDefaultHandler{ 
public: 
  
  bool startElement(const QString &, 
                    const QString &, 
                    const QString &, 
                    const QXmlAttributes&);
  controlAttributs attr;
};
#endif      
