#include "testtimers.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TestTimers * w = new TestTimers();
    QTest::qExec(w);
    return 0;
}
