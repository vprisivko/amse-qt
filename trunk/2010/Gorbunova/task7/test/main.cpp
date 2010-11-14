#include <QApplication>
#include <QTest>

#include "test.h"

int main(int c,char** v){
  QApplication app(c,v);
  Test d;
  QTest::qExec(&d);
  app.exec();
}


