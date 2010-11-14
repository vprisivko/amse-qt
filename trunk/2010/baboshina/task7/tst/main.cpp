#include <QApplication>
#include "tst.h"


int main(int c,char** v){
  QApplication app(c,v);
  Test* d = new Test();
  QTest::qExec(d);
  return 0;
}
