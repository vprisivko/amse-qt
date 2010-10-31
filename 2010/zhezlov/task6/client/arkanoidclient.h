#ifndef ARKANOIDCLIENT_H
#define ARKANOIDCLIENT_H

#include <QWidget>
#include <QtNetwork>
#include <QUdpSocket>
#include <QHostAddress>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTimerEvent>
#include <QtXml>
#include <QDomDocument>
#include <QLineEdit>
#include <QFormLayout>


class ArkanoidClient : public QWidget
{
    Q_OBJECT;

public:
    explicit ArkanoidClient(QWidget *parent = 0);


protected:
    QUdpSocket* socket;
    QPushButton* left;
    QPushButton* right;
    QPushButton* go;
    QPushButton* connectBtn;
    QLineEdit* ipEdit;
    QLineEdit* portEdit;
    bool connected;
    QHostAddress serverIp;
    quint16 serverPort;
    int checkTimerId;
    QString action;
    virtual void timerEvent(QTimerEvent *e);

signals:


public slots:
    void processData();
    void connectPressed();
    void leftPressed();
    void rightPressed();
    void goPressed();
    void buttonReleased();

};

#endif // ARKANOIDCLIENT_H
