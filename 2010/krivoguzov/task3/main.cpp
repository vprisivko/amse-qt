#include <BallWidget.h>
#include <QApplication>

int main (int argc, char** argv){
    QApplication app(argc,argv);
    BallWidget mainWindow(30);
    mainWindow.show();
    app.exec();
}
