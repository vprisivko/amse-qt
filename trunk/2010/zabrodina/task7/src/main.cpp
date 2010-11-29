#include<stdio.h>
#include <QtGui/QApplication>
#include<QDialog>
#include<QPushButton>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QGridLayout>
#include<QRadioButton>
#include<QTextEdit>
#include<QLineEdit>
#include<QCheckBox>
#include<QComboBox>
#include<QLabel>
#include"MyDialog.h"

int main(int argc, char *argv[]) {
QApplication app(argc, argv);
MyDialog dial;
dial.show();
return app.exec();
}

