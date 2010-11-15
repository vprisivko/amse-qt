#include <QApplication>
#include "Test.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Test *test = new Test();
    QTest::qExec(test);
    return 0;
}
