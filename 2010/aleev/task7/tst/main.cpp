#include <QApplication>
#include <QTest>

#include "TimerTest.h"

int main(int argc, char **argv){
    QApplication app(argc, argv);
    TimerTest *t = new TimerTest();
    QTest::qExec(t);

    return 0;
}
