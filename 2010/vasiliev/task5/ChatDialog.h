#ifndef _CHAT_DIALOG_H_
#define _CHAT_DIALOG_H_

#include <QDialog>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QListWidget>
#include <QUdpSocket>

class ChatDialog: public QDialog {

Q_OBJECT;

public:
	ChatDialog(int port, QWidget *parent = 0);

public slots:
	void send();
	void readPendingDatagrams();

private:
	QListWidget *myMessagesList;
	QLineEdit *mySendTextEdt;
	QLabel *myIpLbl;
	QLineEdit *myIpEdt;
	QLabel *myPortLbl;
	QLineEdit *myPortEdt;
	QPushButton *mySendBtn;
	QUdpSocket *mySocket;
	int myPort;

};

#endif // _CHAT_DIALOG_H_
