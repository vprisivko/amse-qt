#include <QApplication>
#include "MainWindow.h"

int main(int argc, char** argv){
    //Q_INIT_RESOUTCE(task4);
    QApplication app(argc,argv);
    MainWindow myMainWindow;
    myMainWindow.show();
    app.exec();
}
