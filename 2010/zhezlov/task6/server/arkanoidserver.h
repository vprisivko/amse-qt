#ifndef ARKANOIDSERVER_H
#define ARKANOIDSERVER_H

#include <QMainWindow>
#include "arkanoidworld.h"
#include <QtNetwork>
#include <QUdpSocket>
#include <QTimerEvent>

class ArkanoidServer : public QMainWindow
{
    Q_OBJECT
public:
    explicit ArkanoidServer(QWidget *parent = 0);
    void SetClientHost( QNetworkAddressEntry& address, quint16 port);

protected:
    ArkanoidWorld* world;
    QUdpSocket* socket;
    quint16 clientPort;
    QHostAddress clientIp;
    void sendState();
    int sendTimerId;
    void timerEvent(QTimerEvent *e);

signals:

public slots:
    void processNewData();

};

#endif // ARKANOIDSERVER_H
