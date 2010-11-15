#include "Test.h"

Test::Test(): QObject() {
    dialog = new Dialog();
}

Test::~Test() {
    delete dialog;
}

void Test::checkSignalOfSetButton() {
    dialog->cmbCheckTimer->setCurrentIndex(0);
    dialog->leInterval->setText("1000");
    QSignalSpy signalSpy(dialog->btnSetInterval, SIGNAL(clicked()));
    QTest::mouseClick(dialog->btnSetInterval, Qt::LeftButton);
    QCOMPARE(1, signalSpy.count());
}

void Test::timeOfFirstTimer() {
    dialog->cmbCheckTimer->setCurrentIndex(0);
    dialog->leInterval->setText("10");
    QTest::mouseClick(dialog->btnSetInterval, Qt::LeftButton);
    QTest::qWait(59);
    QCOMPARE(5, dialog->lTimer1Counter->text().toInt());
}

void Test::timeOfSecondTimer() {
    dialog->cmbCheckTimer->setCurrentIndex(1);
    dialog->leInterval->setText("10");
    QTest::mouseClick(dialog->btnSetInterval, Qt::LeftButton);
    QTest::qWait(59);
    QCOMPARE(5, dialog->lTimer2Counter->text().toInt());
}
