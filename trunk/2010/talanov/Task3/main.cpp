#include "ballwidget.h"

#include <QtGui/QApplication>
#include <QtGui/QColor>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  int ballArea = 1200;
  int updateIntervalInMs = 10;
  QColor ballColor = QColor(255, 0, 0);
  QColor backgroundColor = QColor(0, 0, 0);

  BallWidget w(ballArea, updateIntervalInMs, ballColor, backgroundColor);
  w.show();
  return a.exec();
}
