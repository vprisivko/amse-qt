#include <QtGui/QApplication>
#include <QtCore/QString>

#include "chat.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  if (argc != 2)
  {
    return 1;
  }

  ushort port;
  bool success;
  port = QString(argv[1]).toUShort(&success);
  if (!success)
  {
    return 1;
  }

  Chat w(port);
  w.show();

  return a.exec();
}
