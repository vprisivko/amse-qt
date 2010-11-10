#ifndef TEST_H
#define TEST_H

#include <QTest>
#include <Qt>
#include <QSignalSpy>
#include "../src/Dialog.h"

class Test:public QObject {
Q_OBJECT;
private:
  Dialog* my_dialog;

public:
    Test();
    ~Test();

private slots:

  void set1();
  void set2();
  void time1();
  void time2();


};

#endif

