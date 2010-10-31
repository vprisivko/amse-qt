#ifndef CONTROL_H
#define CONTROL_H

#include <QtGui/QDialog>
#include <QPushButton>
#include<QtNetwork/QUdpSocket>
#include<QtNetwork/QHostAddress>
#include<QByteArray>
#include<QWidget>
#include<QDomDocument>
class ControllState;
class Control : public QDialog
{
    Q_OBJECT;

public:
    Control(QHostAddress _destip, qint16 _destport, qint16 _myport, QWidget *parent = 0);
    ~Control();
    QHostAddress destip;
    qint16 destport;
    qint16 myport;
    QPushButton *leftArrowButton;
    QPushButton *rightArrowButton;
    QPushButton *runButton;
    QUdpSocket *udpSocket;
    ControllState* cSt;
    void createWidgets();
    ControllState* createInstance(QDomDocument *doc);
    void checkState();
public slots:
    void sendRightMessage();
    void sendLeftMessage();
    void sendRunMessage();
    void readMessage();
};
class ControllState {
public:
    int livesleft;
    int xPosition;
    int widthRocket;
    int widthScreen;

};

#endif // CONTROL_H
