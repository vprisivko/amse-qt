#ifndef _CHAT_DIALOG_H_
#define _CHAT_DIALOG_H_

#include <QDialog>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QUdpSocket>

class ChatDialog : public QDialog {

	Q_OBJECT

public:
	ChatDialog(quint16 port, QWidget *parent = 0);
	void createWidgets();
	void fillLayout();

public slots:	
	void sendMessage();
	void receiveMessage();

private:
	QListWidget *myMessagesList;
	QLineEdit *myIPAddressEdit, *myPortEdit, *myMessageEdit;
	QPushButton *mySendButton;
	QUdpSocket *mySocket;

	QHostAddress myIPAddress;
	quint16 myPort;

};

#endif // _CHAT_DIALOG_H_
