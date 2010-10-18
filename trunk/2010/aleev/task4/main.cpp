#include <QApplication>
#include "MainWindow.h"

int main(int argc, char** argv) {
    QApplication app(argc,argv);

    MainWindow mw;
    mw.setWindowTitle("Log calculator");
    mw.show();

    return app.exec();
}
