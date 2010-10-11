#include "ballwidget.h"

#include <QtGui/QApplication>
#include <QtGui/QColor>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  BallWidget w(1300, 2, QColor(255, 0, 0), QColor(0, 255, 0));
  w.show();
  return a.exec();
}
