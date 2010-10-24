#include <QApplication>
#include "MainWindow.h"

int main(int argc, char** argv){
    QApplication app(argc,argv);
    MainWindow myMainWindow;
    myMainWindow.show();
    app.exec();
}
