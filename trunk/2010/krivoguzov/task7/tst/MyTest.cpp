#include <QTest>
#include <QSignalSpy>
#include "MyTest.h"

void MyTest::initTestCase(){
    dialogToTest = new TimerDialog();
}

void MyTest::cleanupTestCase(){
    delete dialogToTest;
}

//Here we will run the first timer
//And then stop and compare the value of timer1 and the count of textChanged signal emisions
void MyTest::firstTimerCheck(){

    //The initial value must be null
    QVERIFY(dialogToTest->number1->text() == QString("0"));

    QSignalSpy mySpy(dialogToTest->number1, SIGNAL(textChanged(QString)));
    QTest::mouseClick(dialogToTest->setButton, Qt::LeftButton);
    QTest::qWait(150);
    QTest::mouseClick(dialogToTest->stopButton, Qt::LeftButton);

    QCOMPARE(mySpy.count(), QString(dialogToTest->number1->text()).toInt());

}

//Testing indexChange with comboBox
void MyTest::comboBoxTest(){

    //The initial value must be Timer1
    QCOMPARE(dialogToTest->myBox->currentText(), QString("Timer1"));

    QSignalSpy mySpy(dialogToTest->myBox, SIGNAL(currentIndexChanged(int)));
    dialogToTest->myBox->setCurrentIndex(1);
    QCOMPARE(mySpy.count(), 1);

    QCOMPARE(dialogToTest->myBox->currentText(), QString("Timer2"));
}

//Here we will run the second timer
//And then stop and compare the value of timer2 and the count of textChanged signal emisions
void MyTest::secondTimerCheck(){

    //The initial value must be null
    QVERIFY(dialogToTest->number2->text() == QString("0"));

    QSignalSpy mySpy(dialogToTest->number2, SIGNAL(textChanged(QString)));
    QTest::mouseClick(dialogToTest->setButton, Qt::LeftButton);
    QTest::qWait(150);
    QTest::mouseClick(dialogToTest->stopButton, Qt::LeftButton);

    QCOMPARE(mySpy.count(), QString(dialogToTest->number2->text()).toInt());

}

//Imitating click on setButton
void MyTest::setButtonClickTest(){

    QSignalSpy mySpy(dialogToTest->setButton,SIGNAL(clicked()));
    QTest::mouseClick(dialogToTest->setButton, Qt::LeftButton);
    QCOMPARE(mySpy.count(), 1);

}

//Imitating click on stopButton
void MyTest::stopButtonClickTest(){

    QSignalSpy mySpy(dialogToTest->stopButton,SIGNAL(clicked()));
    QTest::mouseClick(dialogToTest->stopButton, Qt::LeftButton);
    QCOMPARE(mySpy.count(), 1);

}
