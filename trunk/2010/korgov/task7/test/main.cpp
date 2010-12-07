#include <QApplication>
#include "TestTimerDialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	
    TestTimerDialog timerDialog;

    QTest::qExec(&timerDialog);



    return 0;
}
