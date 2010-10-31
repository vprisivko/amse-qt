#ifndef BALLDIAL_H
#define BALLDIAL_H

#include <QtGui/QDialog>
#include<QPushButton>
#include<QDialog>
#include<QPainter>
#include<QPaintEvent>
#include<QTimerEvent>
#include<QTimer>
#include<QtNetwork/QUdpSocket>
#include<QtNetwork/QHostAddress>
#include<QByteArray>
#include<QLabel>
#include<QXmlContentHandler>
#include<QXmlDefaultHandler>
#include"State.h"
class MyXmlHandler;
class BallDial : public QDialog
{
    Q_OBJECT;

public:
    State *state;
    QLabel *lives;
    QPainter *p;
    QTimer *bTimer;
    QUdpSocket *socket;
    QHostAddress destip;
    qint16 destport;
    qint16 myport;
    MyXmlHandler *xmlH;
    BallDial(QHostAddress _destip, qint16 _destport, qint16 _myport);
    void paintEvent( QPaintEvent *);
    void sendMessage();
public slots:
    void timeEvent();
    void readMessage();

};
class MyXmlHandler : public QXmlDefaultHandler{
public:
    BallDial *bDial;
    MyXmlHandler(BallDial *dial);
    bool startElement ( const QString & namespaceURI,
                                const QString & localName,
                                const QString & qName,
                                const QXmlAttributes & atts );
};

#endif // BALLDIAL_H
