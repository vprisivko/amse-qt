#include "myHandler.h"

bool myHandler::startElement(const QString&, const QString&,
                                                const QString &name, const QXmlAttributes &attrs) {
  if (name == "start") {
    attr.isStarted= true;
 } else {
     attr.isStarted = false;
        }
        if (name == "command") {
               attr.direction = attrs.value("direction").toInt();
        }

        return true;
}
