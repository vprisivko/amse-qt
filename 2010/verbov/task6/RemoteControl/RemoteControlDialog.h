#ifndef REMOTECONTROLDIALOG_H
#define REMOTECONTROLDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QUdpSocket>
#include <QXmlDefaultHandler>

class RemoteControlDialog : public QDialog
{
    Q_OBJECT

public:
    RemoteControlDialog(QHostAddress address, quint16 port,
                        QHostAddress destinationAddress, quint16 destinationPort,
                        QWidget *parent = 0);
    void createWidgets();
    void fillLayout();
    void connectSignalsAndSlots();

public slots:
    void startGame();
    void moveBallToLeft();
    void moveBallToRight();
    void readDatagrams();

private:
        QPushButton *myLeftButton, *myRightButton, *myStartButton;
        QUdpSocket *mySocket;
        QHostAddress myDestinationAddress;
        quint16 myDestinationPort;

private:
        void processTheDatagram(const QByteArray &datagram);
        void sendDatagram(const QString &command);

        class StateHandler : public QXmlDefaultHandler {
        public:
            bool startElement(const QString &, const QString &, const QString &name, const QXmlAttributes &attributes);

            bool myStarted;
            int myWidth;
            int myRacketX, myRacketWidth;
        };
};

#endif // REMOTECONTROLDIALOG_H
