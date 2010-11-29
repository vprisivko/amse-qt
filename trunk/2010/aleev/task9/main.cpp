#include <QApplication>
#include "dialog.h"

int main(int argc, char **argv){
    QApplication app(argc, argv);
    Dialog d;
    d.show();

    return app.exec();
}

