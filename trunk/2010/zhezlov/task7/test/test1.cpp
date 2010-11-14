#include <QSignalSpy>
#include <QComboBox>
#include <QPushButton>
#include "test1.h"


Test1::Test1(QObject *parent) :QObject(parent){

    m_timers = new Timers();

}

void Test1::testSignals(){

    QComboBox* comboBox = m_timers->findChild<QComboBox*>("TimerSwitch");
    QSignalSpy cbSigSpy( comboBox, SIGNAL(currentIndexChanged(int)) );
    comboBox->setCurrentIndex(1);
    comboBox->setCurrentIndex(0);
    QCOMPARE( cbSigSpy.count(), 2 );

    QPushButton* pb = m_timers->findChild<QPushButton*>("setButton");
    QSignalSpy pbSetSigSpy( pb, SIGNAL(clicked(bool)) );
    pb->click();
    QCOMPARE( pbSetSigSpy.count(), 1 );

    pb = m_timers->findChild<QPushButton*>("stopButton");
    QSignalSpy pbStopSigSpy( pb, SIGNAL(clicked(bool)) );
    pb->click();
    QCOMPARE( pbStopSigSpy.count(), 1 );

}


void Test1::testGUI(){

    QPushButton* pbSet = m_timers->findChild<QPushButton*>("setButton");
    QPushButton* pbStop = m_timers->findChild<QPushButton*>("stopButton");

    QTest::keyPress( m_timers->lEd, Qt::Key_1 );
    QTest::keyPress( m_timers->lEd, Qt::Key_0 );
    QTest::keyPress( m_timers->lEd, Qt::Key_0 );
    QTest::mouseClick( pbSet, Qt::LeftButton );
    QTest::mouseClick( pbStop, Qt::LeftButton );
    QCOMPARE( m_timers->lEd->text().toInt(), 100 );

}

void Test1::testSem(){

    QPushButton* pbSet = m_timers->findChild<QPushButton*>("setButton");

    QTest::keyPress( m_timers->lEd, Qt::Key_1 );
    QTest::keyPress( m_timers->lEd, Qt::Key_0 );
    QTest::keyPress( m_timers->lEd, Qt::Key_0 );
    QTest::mouseClick( pbSet, Qt::LeftButton );

    QCOMPARE( m_timers->periods[0], m_timers->lEd->text().toInt() );

}


