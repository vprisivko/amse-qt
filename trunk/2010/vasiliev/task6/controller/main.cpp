#include <QApplication>

#include "RemoteController.h"

int main(int c, char **v) {
    QApplication app(c, v);
    RemoteController controller;
    controller.show();

    return app.exec();
}

