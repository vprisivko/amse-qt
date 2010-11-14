#ifndef TST_H
#define TST_H

#include <QTest>
#include <Qt>
#include <QSignalSpy>
#include "../src/src.h"

class Test:public QObject {
Q_OBJECT;
private:
  myDialog* dialog;

public:
    Test();
    ~Test();

private slots:
  void test1();
  void test2();
  void test3();
  void test4();


};

#endif
