#ifndef BALLDIALOG_H
#define BALLDIALOG_H

#include <QDialog>
#include <QHostAddress>
#include <QDomDocument>
#include <QUdpSocket>
#include <QXmlDefaultHandler>
#include "Ball.h"
#include "Racket.h"

class BallDialog : public QDialog
{
    Q_OBJECT

public:
    BallDialog(QHostAddress address, quint16 port, QHostAddress destinationAddress, quint16 destinationPort,
               int dx, int dy, int rx, int ry, int time, QWidget *parent = 0);
    virtual ~BallDialog();

    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *);
    void resizeEvent(QResizeEvent *);

    QDomDocument serialize();

    void startGame();
    void moveRacketLeft();
    void moveRacketRight();

public slots:
    void readDatagrams();

private:
    Ball *myBall;
    Racket *myRacket;
    QHostAddress myDestinationAddress;
    quint16 myDestinationPort;
    bool myIsStarted;
    QUdpSocket *mySocket;
    int myRacketSpeed;
    int myBallsLeft, myBallsCount;

private:
    void processTheDatagram(const QByteArray &datagram);

    class CommandHandler : public QXmlDefaultHandler {

    public:
        CommandHandler();
        bool startElement(const QString &, const QString &, const QString &name, const QXmlAttributes &);

        bool myStarted;
        int myDirection;

    };

};



#endif // BALLDIALOG_H
