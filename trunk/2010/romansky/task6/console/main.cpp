#include <QApplication>

#include "Console.h"

int main(int c,char** v){
  QApplication app(c,v);
  QString s;
  if (c>2) {
    s = v[2];
    Console d(NULL, v[1], s.toInt());
    d.show();
    return app.exec();
  } else {
    Console d(NULL, "127.0.0.1", 10000);
    d.show();
    return app.exec();
  }
  return 0;
}
