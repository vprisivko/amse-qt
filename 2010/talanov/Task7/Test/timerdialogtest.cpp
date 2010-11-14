#include "timerdialogtest.h"

#include <QtTest/QSignalSpy>
#include <QtTest/QtTest>

#include <QtGui/QPushButton>

TimerDialogTest::TimerDialogTest(QObject *parent)
  : QObject(parent)
{
  myTimerDialog = new TimerDialog();
}

TimerDialogTest::~TimerDialogTest()
{

}

void TimerDialogTest::testLogic()
{
  myTimerDialog->setActiveTimer(0);
  QCOMPARE(myTimerDialog->myActiveTimerIndex, 0);
  myTimerDialog->resetActiveTimer();
  QCOMPARE(myTimerDialog->myCountLabel1->text().toInt(), 0);
  myTimerDialog->setCurrentInterval("235");
  QCOMPARE(myTimerDialog->myCurrentInterval, 235);
  myTimerDialog->setCurrentInterval("sdfsd");
  QCOMPARE(myTimerDialog->myCurrentInterval, 235);
}

void TimerDialogTest::testInterfaceAndSignals()
{
  QPushButton* setButton = myTimerDialog->findChild<QPushButton*>("setButton");
  QPushButton* stopButton = myTimerDialog->findChild<QPushButton*>("stopButton");

  QSignalSpy setButtonSpy(setButton, SIGNAL(clicked()));
  QSignalSpy stopButtonSpy(stopButton, SIGNAL(clicked()));

  myTimerDialog->setActiveTimer(0);
  //test that button clicks work properly
  QTest::mouseClick(setButton, Qt::LeftButton);
  QVERIFY(myTimerDialog->myTimerId2 == 0);
  QTest::mouseClick(stopButton, Qt::LeftButton);
  myTimerDialog->setActiveTimer(1);
  QTest::mouseClick(setButton, Qt::LeftButton);
  QVERIFY(myTimerDialog->myTimerId2 != 0);
  QCOMPARE(setButtonSpy.count(), 2);
  QCOMPARE(stopButtonSpy.count(), 1);
}

void TimerDialogTest::testToFail()
{
  QVERIFY(myTimerDialog == NULL);
}