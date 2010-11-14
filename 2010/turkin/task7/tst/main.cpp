#include <QApplication>
#include <QTest>

#include "TimerDialogTest.h"


int main(int c,char** v){
  QApplication app(c,v);
  TimerDialogTest* t = new TimerDialogTest();
  QTest::qExec(t);
  return 0;
}
