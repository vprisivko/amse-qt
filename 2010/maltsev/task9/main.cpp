#include <QApplication>
#include "Dialog.h"

int main(int n, char **v) {
  QApplication a(n, v);
  Dialog d;
  d.show();
  return a.exec();
}
