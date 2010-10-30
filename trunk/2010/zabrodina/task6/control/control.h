#ifndef CONTROL_H
#define CONTROL_H

#include <QtGui/QDialog>
#include <QPushButton>
#include<QtNetwork/QUdpSocket>
#include<QByteArray>
#include<QWidget>
class Control : public QDialog
{
    Q_OBJECT;

public:
    Control(int _port,QWidget *parent = 0);
    ~Control();
    int port;
    QPushButton *leftArrowButton;
    QPushButton *rightArrowButton;
    QPushButton *runButton;
    QUdpSocket *ballSocket;
    void createWidgets();
};

#endif // CONTROL_H
