#include "test.h"

MyTest :: MyTest() : QObject(){
    myDialog = new MyDialog();
}

MyTest :: ~MyTest(){
    delete myDialog;
}

void MyTest :: testSetTimerValue(){
    myDialog->timerComboBox->setCurrentIndex( 1 );
    QTest :: keyPress( myDialog->timerEditBox, Qt :: Key_1 );
    QTest :: keyPress( myDialog->timerEditBox, Qt :: Key_2 );
    QTest :: keyPress( myDialog->timerEditBox, Qt :: Key_3 );
    QTest :: mouseClick( myDialog->setButton, Qt :: LeftButton );
    QCOMPARE( myDialog->timerEditBox->text().toInt(), 123 );
}

void MyTest :: testSetButton(){
    myDialog->timerComboBox->setCurrentIndex( 0 );
    myDialog->timerEditBox->setText( "123" );
    QSignalSpy sigSpy( myDialog, SIGNAL( setSignal() ) );
    QTest :: mouseClick( myDialog->setButton, Qt :: LeftButton );
    QCOMPARE( 1, sigSpy.count() );
}

void MyTest :: testChangeTimers(){
    myDialog->timerComboBox->setCurrentIndex( 0 );
    QSignalSpy sigSpy( myDialog->timerComboBox, SIGNAL( currentIndexChanged( int ) ) );
    myDialog->timerComboBox->setCurrentIndex( 1 );
    myDialog->timerComboBox->setCurrentIndex( 0 );
    myDialog->timerComboBox->setCurrentIndex( 1 );
    QCOMPARE( 3, sigSpy.count() );
}

void MyTest :: testTimer(){
    myDialog->timerComboBox->setCurrentIndex( 0 );
    myDialog->timerEditBox->setText( "100" );
    int timerValue = myDialog->t1Value->intValue();
    QTest :: mouseClick( myDialog->setButton, Qt :: LeftButton );
    QTest :: qWait( 1234 );
    QCOMPARE( timerValue + 12, myDialog->t1Value->intValue() );
}
