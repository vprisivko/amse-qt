#ifndef UDPCHAT_H
#define UDPCHAT_H

#include <QtGui/QWidget>
#include <QDialog>
#include <QListWidget>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QByteArray>
#include <QtNetwork/QUdpSocket>
#include <QMessageBox>

#define MIN_HEIGHT 100
#define MY_IP "127.0.0.1"

class UDPChat : public QDialog
{
    Q_OBJECT

    qint16 m_port;

    QListWidget * m_historyOfTheTalk;
    QLineEdit * m_portOfThePartner;
    QLineEdit * m_ipOfThePartner;
    QTextEdit * m_messageToSend;
    QPushButton * m_send;
    QUdpSocket * m_udpSocket;

public:
    UDPChat(quint16 port,QWidget *parent = 0);
    ~UDPChat() {}

private:
	void createItems();
	void putItemsOnTheForm();
	void connectAllTheStuff();

public slots:
	void receiveMessage();
	void sendMessage();
};

#endif // UDPCHAT_H
