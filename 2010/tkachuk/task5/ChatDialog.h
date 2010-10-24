#ifndef CHATDIALOG_H
#define CHATDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QListWidget>
#include <QUdpSocket>

class ChatDialog : public QDialog
{
	Q_OBJECT

public:
	ChatDialog(quint16 port, QWidget *parent = 0);

public slots:
	void sendMessage();
	void receiveMessage();

private:
	QListWidget *myListWidget;
	QLineEdit *myLineEditIp;
	QLineEdit *myLineEditPort;
	QLineEdit *myLineEditMessage;
	QPushButton *mySendButton;
	QUdpSocket *myUdpSocket;
};

#endif // CHATDIALOG_H
