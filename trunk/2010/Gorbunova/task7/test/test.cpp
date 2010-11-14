#include <QTest>
#include <Qt>
#include <QtTest>
#include <QSignalSpy>
#include "test.h"

Test::Test():QObject(){
  myDialog = new Dialog();
}

Test::~Test(){
  delete myDialog;
}

void Test::setTimer1(){
  myDialog->Combo->setCurrentIndex(1);
  QSignalSpy mySpy(myDialog->Combo, SIGNAL(currentIndexChanged(int)));
  myDialog->Combo->setCurrentIndex(0);
  myDialog->setline->setText("1000");
  QTest::mouseClick(myDialog->set,Qt::LeftButton);
  QCOMPARE(1,mySpy.count());
}

void Test::setTimer2(){
  myDialog->Combo->setCurrentIndex(1);
  myDialog->setline->setText("");
  QTest::keyPress(myDialog->setline,Qt::Key_1);
  QTest::keyPress(myDialog->setline,Qt::Key_0);
  QTest::keyPress(myDialog->setline,Qt::Key_0);
  QTest::keyPress(myDialog->setline,Qt::Key_0);
  QTest::mouseClick(myDialog->set,Qt::LeftButton);
  QCOMPARE(1000,myDialog->setline->text().toInt());
}
void Test::setChangeTimers(){
  myDialog->Combo->setCurrentIndex(0);
  QSignalSpy mySpy(myDialog->Combo, SIGNAL(currentIndexChanged(int)));
  myDialog->Combo->setCurrentIndex(1);
  myDialog->Combo->setCurrentIndex(0);
  QCOMPARE(2,mySpy.count());
}

void Test::time1(){
  myDialog->Combo->setCurrentIndex(0);
  myDialog->setline->setText("100");
  int timer = myDialog->timerLabel1->text().toInt();
  QTest::mouseClick(myDialog->set,Qt::LeftButton);
  QTest::qWait(2120);
  QCOMPARE(timer + 21,myDialog->timerLabel1->text().toInt());
}

