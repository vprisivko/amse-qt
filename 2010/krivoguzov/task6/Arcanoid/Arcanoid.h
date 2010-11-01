#ifndef ARCANOID_H
#define ARCANOID_H
#include <QWidget>
#include <QUdpSocket>

class Arcanoid : public QWidget {
    Q_OBJECT;

public:
    Arcanoid(QString destIP, int destPort, int portToListen, int BallRadius = 20, QWidget *parent = 0);
    void paintEvent(QPaintEvent *);

private slots:
    void newControlArrived();
    void sendCurrentState();

private:
    void configureNetwork();
    QByteArray createDomByteArray();

private:
    int BallRadius;
    double deskX, deskY;
    double mySpeed;
    double myAngle;
    double myCurrentX,myCurrentY;
    double myDX,myDY;

    QTimer *myTimer;
    int lifesLeft;
    bool isPaused;

    QString destIp;
    int destPort;
    int portToListen;
    QUdpSocket* myUdpSocket;

};

#endif // ARCANOID_H
