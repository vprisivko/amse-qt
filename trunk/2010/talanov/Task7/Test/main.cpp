#include <QtGui/QApplication>
#include <QtTest/QTest>
#include "timerdialogtest.h"

int main( int c, char** v ){

  QApplication app(c, v);
  TimerDialogTest test;
  return QTest::qExec(&test);
}
