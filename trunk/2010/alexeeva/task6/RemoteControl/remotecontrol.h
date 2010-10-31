#ifndef REMOTECONTROL_H
#define REMOTECONTROL_H

#include <QPushButton>
#include <QLineEdit>
#include <QHostAddress>
#include <QKeyEvent>
#include <QXmlDefaultHandler>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QUdpSocket>
#include <QIntValidator>

#include <QtGui/QDialog>

class RemoteControl : public QDialog
{
    Q_OBJECT

public:
    RemoteControl(QHostAddress, qint16, QWidget *parent = 0);
    ~RemoteControl() {}

public slots:
	void moveRight();
	void moveLeft();
	void start();
	void setSocket();

private:
    struct State {
        static State * createInstance(const QByteArray&, RemoteControl *);
        bool active;
    };

    class RCXmlHandler: public QXmlDefaultHandler {
    public:
        RCXmlHandler(State * state, RemoteControl * rc): m_state(state), m_remoteControl(rc) {}
        bool startElement(const QString &, const QString &, const QString &, const QXmlAttributes &);
    private:
        State * m_state;
        RemoteControl * m_remoteControl;
    };

    void processTheDatagram(QByteArray datagram);

private slots:
	void readPendingDatagrams();
	void enableStart();
	void enableMove();

private:
    /* Buttons and lineEdits */
    QLineEdit * m_ipInput;
    QLineEdit * m_portInput;
    QPushButton * m_setSocket;

    QPushButton * m_pushRight;
    QPushButton * m_pushLeft;
    QPushButton * m_start;

    /* Some stuff connected with the network */
    QUdpSocket * m_udpSocket;

    QHostAddress m_ipTo;
    qint16 m_portTo;
};

#endif // REMOTECONTROL_H
