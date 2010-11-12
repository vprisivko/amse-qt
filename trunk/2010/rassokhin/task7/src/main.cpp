#include <QApplication>
#include "timersdialog.h"

int main (int argc, char ** argv) {
    QApplication app(argc, argv);
    TimersDialog td;
    td.show();
    return app.exec();
}
