#ifndef PULT_H
#define PULT_H

#include <QDialog>
#include <QPushButton>
#include <QUdpSocket>
#include <QHostAddress>
#include <QByteArray>
#include <QXmlDefaultHandler>

class Pult : public QDialog {
    Q_OBJECT

private:
    QPushButton *bnStart;
    QPushButton *bnLeft;
    QPushButton *bnRight;

    QHostAddress myHost;
    qint16 myPort;
    QHostAddress toHost;
    qint16 toPort;
    QUdpSocket *udpSocket;

    void setNetworkData(char *ip, int port);
    void setWidgets();
    void connects();

public:
    Pult(char* myIp, int myPort, char* toIp, int toPort, QWidget *parent = 0);

    struct State {
        int ballX, ballY, ballRadius;
        int racketX, racketHalfWidth;
        int fieldWidth;
        bool gameOver;
        static State* createInstance(const QByteArray &str);
    };

    class PultXmlHandler: public QXmlDefaultHandler {
    private:
        State *state;
    public:
        PultXmlHandler(State *state) : state(state) {}
        bool startElement(const QString&, const QString&, const QString &name, const QXmlAttributes &attrs);
    };

    void parseDatagramm(QByteArray &str);

public slots:
    void readDatagrams();
    void pushStart();
    void pushLeft();
    void pushRight();
};

#endif // PULT_H
