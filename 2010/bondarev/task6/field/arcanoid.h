#ifndef ARCANOID_H
#define ARCANOID_H

#include <QDialog>
#include <QHostAddress>
#include <QUdpSocket>
#include <QDomElement>
#include <QTimerEvent>
#include <QXmlDefaultHandler>

class Arcanoid : public QDialog {
    Q_OBJECT

private:

    struct Racket {
        int x;
        int width;
        int height;
        int dx;

        Racket();
        void move(Arcanoid *state);
        QDomElement serialize(QDomDocument &doc);
    };

    struct Ball {
        int x;
        int y;
        int radius;
        int dx;
        int dy;

        Ball();
        void move(Racket* racket, Arcanoid *state);
        QDomElement serialize(QDomDocument &doc);
    };

    class FieldXmlHandler: public QXmlDefaultHandler {
    private:
        Arcanoid *myField;
    public:
        FieldXmlHandler(Arcanoid *field): myField(field) {}
        bool startElement(const QString &, const QString &, const QString &, const QXmlAttributes &);
    };

    int countBallForGame;
    bool gameOver;
    Racket *racket;
    Ball *ball;

    int timerId;

    QHostAddress myHost;
    qint16 myPort;
    QHostAddress toHost;
    qint16 toPort;
    QUdpSocket *udpSocket;

    void setBeginState();
    void setNetworkData(QHostAddress &, qint16);

    QDomDocument serialize();
    void parseDatagram(QByteArray &str);
    void sendState();

public:
    Arcanoid(QHostAddress ip, qint16 port, QWidget *parent = 0);

public slots:
    void readDatagrams();
    void timerEvent(QTimerEvent *);
    void paintEvent(QPaintEvent *);
};

#endif // ARCANOID_H
