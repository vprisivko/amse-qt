#include <QApplication>
#include "balldialog.h"

int main(int argc, char* argv[]){
    QApplication app(argc, argv);
    ballDialog dialog;
    dialog.show();
    return app.exec();
}
