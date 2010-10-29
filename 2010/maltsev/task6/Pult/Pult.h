#ifndef PULT_H
#define PULT_H

#include <QDialog>
#include <QUdpSocket>
#include <QHostAddress>
#include <QByteArray>
#include <QPushButton>
#include <QLineEdit>
#include <QXmlDefaultHandler>

class Pult: public QDialog {
Q_OBJECT;

public:
    Pult(QHostAddress&, qint16, QWidget *parent = 0);

private:
    QPushButton *my_leftButton, *my_rightButton, *my_setButton, *my_startButton;
    QLineEdit *my_ipEdit, *my_portEdit;
    QUdpSocket *my_udpSocket;
    QHostAddress my_ip, my_ipTo;
    qint16 my_port, my_portTo;
    bool isSet;

    void setView();
    void setNetworkData();
    void connectButtons();

    struct TableState {
        static TableState* createInstance(const QByteArray&);
        bool gameOver, started;
        int ballX, ballY, tableX, tableHW, height, width;

    };

    class PultXmlHandler: public QXmlDefaultHandler {
    public:
        PultXmlHandler(TableState* ts):my_ts(ts){}
        bool startElement(const QString &, const QString &, const QString &, const QXmlAttributes &);
    private:
        TableState* my_ts;

    };

    void processTheDatagram(QByteArray datagram);

private slots:
    void readPendingDatagrams();
    void sendRight();
    void sendLeft();
    void setContact();
    void sendStart();
    void sendStop();

    friend class Pult::PultXmlHandler;
};

#endif
