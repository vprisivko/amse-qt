/*
 * File:   main.cpp
 * Author: andrey
 *
 * Created on October 10, 2010, 4:10 PM
 */

#include <QtGui/QApplication>

#include "BallDialog.h"

int main(int argc, char *argv[]) {
    // initialize resources, if needed
    // Q_INIT_RESOURCE(resfile);

    QApplication app(argc, argv);

    // create and show your widgets here
    BallDialog ball;
    ball.show();

    return app.exec();
}
