#ifndef _UDPCHAT_H_
#define _UDPCHAT_H_

#include <QtNetwork/QUdpSocket>
#include <QDialog>
#include <QLineEdit>
#include <QListWidget>


class UdpChat : public QDialog
{
	Q_OBJECT;

public:
	UdpChat(QWidget *parent = 0, int port = -1);

private:
	void configureUI();
	void configureUdp(int port);

private slots:
	void receiveMessage();
	void sendMessage();

private:
	QUdpSocket *socket_;
	QListWidget *messages_;
	QLineEdit *ipAddress_;
	QLineEdit *ipPort_;
	QLineEdit *message_;
};

#endif
