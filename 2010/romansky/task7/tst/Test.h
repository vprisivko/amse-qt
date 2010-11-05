#ifndef TEST_H
#define TEST_H
#include <QTest>
#include <QTimer>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <Qt>
#include <QSignalSpy>
#include <QTestEventList>
#include "../src/TimeDialog.h"
class Test:public QObject{
  Q_OBJECT;
  private:
  TimeDialog* mytimedialog;
  QTimer* mytimer;
  int mybegintime;
  int mytimeafterperiod;
  int mynumberofperiods;
  bool periodended;
  public:
  Test();
  Test(TimeDialog* timedialog);
  void timeSpending();
  public slots:
  void endperiod();
  private slots:
  void firstbegintime();
  void firsttestSet();
  void firsttestStop();
  void firstendtime();
  void secondbegintime();
  void secondtestSet();
  void secondtestStop();
  void secondendtime();

};

#endif

