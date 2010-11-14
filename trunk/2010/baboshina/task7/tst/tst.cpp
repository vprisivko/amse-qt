#include "tst.h"
#include "../src/src.h"

Test::Test(): QObject() {
    dialog = new myDialog();
}

Test::~Test() {
    delete dialog;
}

void Test::test1() {
    dialog->cbChoose->setCurrentIndex(0);
    dialog->leInt->setText("150");

    QSignalSpy sSet(dialog, SIGNAL(isSet()));
    QSignalSpy sStop(dialog, SIGNAL(isStop()));

    QTest::mouseClick(dialog->btnSet, Qt::LeftButton);
    QTest::mouseClick(dialog->btnStop, Qt::LeftButton);

    QCOMPARE(1, sSet.count());
    QCOMPARE(1, sStop.count());
}

void Test::test2() {
    dialog->cbChoose->setCurrentIndex(1);
    dialog->leInt->setText("150");

    QSignalSpy sSet(dialog, SIGNAL(isSet()));
    QSignalSpy sStop(dialog, SIGNAL(isStop()));

    QTest::mouseClick(dialog->btnSet, Qt::LeftButton);
    QTest::mouseClick(dialog->btnStop, Qt::LeftButton);

    QCOMPARE(1, sSet.count());
    QCOMPARE(1, sStop.count());
}

void Test::test3() {
    dialog->cbChoose->setCurrentIndex(0);
    dialog->leInt->setText("101");

    QTest::mouseClick(dialog->btnSet, Qt::LeftButton);
    QTest::qWait(5000);

    QCOMPARE(dialog->lbltimer1->text().toInt(), 49);
}

void Test::test4() {
    dialog->cbChoose->setCurrentIndex(1);
    dialog->leInt->setText("101");

    QTest::mouseClick(dialog->btnSet, Qt::LeftButton);
    QTest::qWait(5000);

    QCOMPARE(dialog->lbltimer2->text().toInt(), 49);
}

