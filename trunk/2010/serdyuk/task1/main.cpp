// =====================================================================================
// 
//       Filename:  main.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  24.09.2010 16:27:09
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Dmitriy Serdyuk (), serdyuk.dmitriy@gmail.com
//        Company:  
// 
// =====================================================================================

#include <QApplication>
#include <QWidget>
#include <QBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QWidget mainWidget;
    QHBoxLayout mainLayout;
    mainWidget.setLayout(&mainLayout);

    QVBoxLayout adressBookLayout;
    mainLayout.addLayout(&adressBookLayout);

    QLabel nameLabel("Name: ", &mainWidget);
    QLineEdit nameEdit(&mainWidget);
    QHBoxLayout nameLayout;
    adressBookLayout.addLayout(&nameLayout);
    nameLayout.addWidget(&nameLabel);
    nameLayout.addWidget(&nameEdit);

    QLabel adressLabel("Adress: ", &mainWidget);
    QLineEdit adressEdit(&mainWidget);
    QHBoxLayout adressLayout;
    adressBookLayout.addLayout(&adressLayout);
    adressLayout.addWidget(&adressLabel);
    adressLayout.addWidget(&adressEdit);

    QLabel commentsLabel("Comments: ", &mainWidget);
    QTextEdit commentsEdit(&mainWidget);
    QHBoxLayout commentsLayout;
    adressBookLayout.addLayout(&commentsLayout);
    commentsLayout.addWidget(&commentsLabel);
    commentsLayout.addWidget(&commentsEdit);

    QVBoxLayout buttonsLayout;
    mainLayout.addLayout(&buttonsLayout);

    QPushButton okButton("Ok", &mainWidget);
    QPushButton cancelButton("Cancel", &mainWidget);
    buttonsLayout.addWidget(&okButton);
    buttonsLayout.addWidget(&cancelButton);

    mainWidget.show();
    return app.exec();
}

