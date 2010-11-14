#ifndef _TEST_
#define _TEST_

#include <QObject>
#include "../src/Dialog.h"

class Test : public QObject{
  Q_OBJECT;
public:
  Dialog* myDialog;
  Test();
  ~Test();
private slots:
  void setTimer1();
  void setTimer2();
  void time1();
  void setChangeTimers();
};
#endif
