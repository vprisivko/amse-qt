// =====================================================================================
// 
//       Filename:  test.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  14.11.2010 21:37:31
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Dmitriy Serdyuk (), serdyuk.dmitriy@gmail.com
//        Company:  
// 
// =====================================================================================

#include <QSignalSpy>
#include <QTest>

#include "test.h"

Test::Test(QObject *parent) : QObject(parent), myDialog(new Dialog()) {
}

Test::~Test() {
    delete myDialog;
}

void Test::testFirstSet() {
    myDialog->myComboBox->setCurrentIndex(0);
    myDialog->mySetLineEdit->setText("1000");
    QSignalSpy signalSpy(myDialog, SIGNAL(setPressed()));

    QTest::mouseClick(myDialog->mySetButton, Qt::LeftButton);
    QCOMPARE(1, signalSpy.count());
}

void Test::testSecondSet() {
    myDialog->myComboBox->setCurrentIndex(1);
    myDialog->mySetLineEdit->setText("1000");
    QSignalSpy signalSpy(myDialog, SIGNAL(setPressed()));

    QTest::mouseClick(myDialog->mySetButton, Qt::LeftButton);
    QCOMPARE(1, signalSpy.count());
}

void Test::testFirstTimer() {
    myDialog->myComboBox->setCurrentIndex(0);
    myDialog->mySetLineEdit->setText("100");
    int startValue = myDialog->myTimer1;
    QTest::mouseClick(myDialog->mySetButton, Qt::LeftButton);
    QTest::qWait(1000);
    QCOMPARE(startValue + 9, myDialog->myTimer1);
}

void Test::testSecondTimer() {
    myDialog->myComboBox->setCurrentIndex(1);
    myDialog->mySetLineEdit->setText("100");
    int startValue = myDialog->myTimer2;
    QTest::mouseClick(myDialog->mySetButton, Qt::LeftButton);
    QTest::qWait(1000);
    QCOMPARE(startValue + 9, myDialog->myTimer2);
}
    
void Test::testStopFirst() {
    myDialog->myComboBox->setCurrentIndex(0);
    myDialog->mySetLineEdit->setText("10");

    int startValue = myDialog->myTimer1;
    QTest::mouseClick(myDialog->mySetButton, Qt::LeftButton);
    QTest::mouseClick(myDialog->myStopButton, Qt::LeftButton);

    QTest::qWait(100);

    QCOMPARE(startValue, myDialog->myTimer1);
}
    
void Test::testStopSecond() {
    myDialog->myComboBox->setCurrentIndex(1);
    myDialog->mySetLineEdit->setText("10");

    int startValue = myDialog->myTimer2;
    QTest::mouseClick(myDialog->mySetButton, Qt::LeftButton);
    QTest::mouseClick(myDialog->myStopButton, Qt::LeftButton);

    QTest::qWait(100);

    QCOMPARE(startValue, myDialog->myTimer2);
}
