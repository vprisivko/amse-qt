#include <QApplication>
#include "Table.h"

int main(int n, char **v) {
  QApplication a(n, v);
  Table t;
  t.show();
  return a.exec();
}
