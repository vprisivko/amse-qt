#ifndef TABLE_H
#define TABLE_H

#include <QDialog>
#include <QPaintEvent>
#include <QTimerEvent>
#include <QUdpSocket>
#include <QByteArray>
#include <QDomDocument>
#include <QDomElement>
#include <QXmlDefaultHandler>

const int BALL_RADIUS = 20;
const int BALL_AVERAGE_SPEED = 16;
const int BALL_TIMER_INTERVAL = 25;
const int SEND_TIMER_INTERVAL = 250;
const int TABLE_HEIGHT = 600;
const int TABLE_WIDTH = 800;
const int RACKET_HEIGHT = 20;
const int RACKET_HALFWIDTH = 80;
const int RACKET_SPEED = 20;
const int BALLS_NUMBER = 3;

class Table: public QDialog {
Q_OBJECT;

public:
    Table(QHostAddress&, qint16, QWidget *parent = 0);
    ~Table();

private:

    QDomDocument serialize();

    struct Racket {
        int my_x, my_dx, my_height, my_width;
        void move();
        QDomElement serialize(QDomDocument &doc);
    } my_racket;

    struct Ball {
        int my_x, my_y, my_r, my_rxEff, my_ryEff, my_dx, my_dy;
        void move(Racket&, Table*);
        QDomElement serialize(QDomDocument &doc);
    } my_ball;

    class TableXmlHandler: public QXmlDefaultHandler {
    public:
        TableXmlHandler(Table* table):my_table(table){}
        bool startElement(const QString &, const QString &, const QString &, const QXmlAttributes &);
    private:
        Table* my_table;
    };

    int my_ballTimerID, my_stateTimerID, my_ballsNumber;
    QUdpSocket *my_udpSocket;
    QHostAddress my_ip, my_ipTo;
    qint16 my_port, my_portTo;
    bool started;
    bool pultConnected;
    bool gameOver;

    void processTheDatagram(QByteArray datagram);
    void sendState();
    void loseBall();

protected:
    virtual void paintEvent(QPaintEvent*);
    virtual void timerEvent(QTimerEvent*);

private slots:
    void readPendingDatagrams();

    friend class Table::TableXmlHandler;
    friend class Table::Ball;

};

#endif
