#include <QApplication>
#include "Log.h"

int main(int n, char **v) {
  QApplication a(n, v);
  Log l;
  l.show();
  return a.exec();
}
