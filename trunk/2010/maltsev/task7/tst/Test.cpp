#include "Test.h"

Test::Test(): QObject() {
    my_dialog = new Dialog();
}

Test::~Test() {
     delete my_dialog;
}

void Test::set1() {
    my_dialog->my_cbox->setCurrentIndex(0);
    my_dialog->my_edit->setText("100");
    QSignalSpy s1(my_dialog, SIGNAL(setSignal()));
    QTest::mouseClick(my_dialog->my_setbtn, Qt::LeftButton);
    QCOMPARE(1, s1.count());
}

void Test::set2() {
    my_dialog->my_cbox->setCurrentIndex(1);
    my_dialog->my_edit->setText("100");
    QSignalSpy s1(my_dialog, SIGNAL(setSignal()));
    QTest::mouseClick(my_dialog->my_setbtn, Qt::LeftButton);
    QCOMPARE(1, s1.count());
}

void Test::time1() {
    my_dialog->my_cbox->setCurrentIndex(0);
    my_dialog->my_edit->setText("152");
    int time1 = my_dialog->my_label1->text().toInt();
    QTest::mouseClick(my_dialog->my_setbtn, Qt::LeftButton);
    QTest::qWait(1550);
    QCOMPARE(time1 + 10, my_dialog->my_label1->text().toInt());
}

void Test::time2() {
    my_dialog->my_cbox->setCurrentIndex(1);
    my_dialog->my_edit->setText("152");
    int time2 = my_dialog->my_label2->text().toInt();
    QTest::mouseClick(my_dialog->my_setbtn, Qt::LeftButton);
    QTest::qWait(1550);
    QCOMPARE(time2 + 10, my_dialog->my_label2->text().toInt());
}
