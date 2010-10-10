#include<stdio.h>
#include<QApplication>
#include<QPushButton>
#include<QDialog>
#include<QVBoxLayout>
#include"ball.h"
int main(int c, char *v[]) {
    QApplication app( c, v );
    BallDialog ballDialog;
    ballDialog.show();
    app.exec();
}
