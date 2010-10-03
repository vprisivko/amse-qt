#include <TimerDialog.h>
#include <QApplication>

int main(int argc, char **argv){
    QApplication app(argc,argv);
    TimerDialog mainDialog;
    mainDialog.show();
    return app.exec();
}
