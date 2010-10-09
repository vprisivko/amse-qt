#include "moveDialog.h"
#include <QApplication>

int main(int argc, char** argv) {
    QApplication app(argc,argv);
    moveDialog md;
    md.show();

    return app.exec();
} 
