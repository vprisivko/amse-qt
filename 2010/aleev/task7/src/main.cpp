#include <QApplication>
#include "dialog.h"

int main(int argc, char **argv){
    QApplication app(argc, argv);
    Dialog d;
    d.setWindowTitle("Timers");
    d.show();
    return app.exec();
}

