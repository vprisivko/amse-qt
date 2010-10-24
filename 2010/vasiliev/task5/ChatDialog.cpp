#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHostAddress>
#include <QByteArray>
#include <iostream>

#include "ChatDialog.h"

ChatDialog::ChatDialog(int port, QWidget *parent): QDialog(parent), myPort(port) {

	setWindowTitle(QString("Mini Chat is working on port: ") + QString::number(port));

	myMessagesList = new QListWidget(this);
	myIpLbl = new QLabel("IP: ", this);
	myIpEdt = new QLineEdit(this);
	myPortLbl = new QLabel("Port: ", this);
	myPortEdt = new QLineEdit(this);
	mySendTextEdt = new QLineEdit(this);
	mySendBtn = new QPushButton("Send", this);
	mySocket = new QUdpSocket(this);

	setLayout(new QVBoxLayout(this));
	layout()->addWidget(myMessagesList);

	QHBoxLayout *lay = new QHBoxLayout();
	lay->addWidget(myIpLbl);
	lay->addWidget(myIpEdt);
	lay->addWidget(myPortLbl);
	lay->addWidget(myPortEdt);
	layout()->addItem(lay);

	lay = new QHBoxLayout();
	lay->addWidget(mySendTextEdt);
	lay->addWidget(mySendBtn);
	layout()->addItem(lay);

	if (!mySocket->bind(port)) {
		std::cerr << "Try to use another port. Port #" << port << " is already used!\n"; 
		exit(-1);
	}

	QObject::connect(mySendBtn, SIGNAL(pressed()), this, SLOT(send()));
	QObject::connect(mySocket, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams()));

}

void ChatDialog::send() {
	QByteArray datagram(mySendTextEdt->text().toUtf8().data());
	mySocket->writeDatagram(datagram.data(), QHostAddress(myIpEdt->text()), myPortEdt->text().toUInt());
	myMessagesList->addItem("I wrote: " + mySendTextEdt->text());
	mySendTextEdt->setText("");
}

void ChatDialog::readPendingDatagrams() {
	while (mySocket->hasPendingDatagrams()) {
		QByteArray datagram;
		datagram.resize(mySocket->pendingDatagramSize());
		QHostAddress sender;
		quint16 senderPort;

		mySocket->readDatagram(datagram.data(), datagram.size(),
					&sender, &senderPort);

		QString data(datagram);
		myMessagesList->addItem(sender.toString() + ":" + QString::number(senderPort) + " wrote: " + data);
	}
}
