#include <QApplication>
#include "myWindow.h"

int main(int n, char **v) {
  QApplication a(n, v);
  myWindow l;
  l.show();
  return a.exec();
}
