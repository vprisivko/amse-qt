#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include "ChatDialog.h"

ChatDialog::ChatDialog(quint16 port, QWidget *parent) : QDialog(parent) {
	mySocket = new QUdpSocket(this);
	mySocket->bind(QHostAddress::LocalHost, port);
	
	setWindowTitle("UDP Chat");
	createWidgets();
	fillLayout();

	connect(mySendButton, SIGNAL(pressed()), this, SLOT(sendMessage()));
	connect(mySocket, SIGNAL(readyRead()), this, SLOT(receiveMessage()));
}

void ChatDialog::createWidgets() {
	myMessagesList = new QListWidget(this);
	myIPAddressEdit = new QLineEdit("127.0.0.1", this);
	myPortEdit = new QLineEdit(this);
	myMessageEdit = new QLineEdit(this);
	mySendButton = new QPushButton("Send", this);
}

void ChatDialog::fillLayout() {
	QHBoxLayout *addressLayout = new QHBoxLayout();
	addressLayout->addWidget(new QLabel("IP address: ", this));
	addressLayout->addWidget(myIPAddressEdit);
	addressLayout->addWidget(new QLabel("Port: ", this));
	addressLayout->addWidget(myPortEdit);

	QHBoxLayout *sendLayout = new QHBoxLayout();
	sendLayout->addWidget(new QLabel("Message: ", this));
	sendLayout->addWidget(myMessageEdit);
	sendLayout->addWidget(mySendButton);

	setLayout(new QVBoxLayout());
	layout()->addWidget(new QLabel("Messages:", this));
	layout()->addWidget(myMessagesList);
	layout()->addItem(addressLayout);
	layout()->addItem(sendLayout);
}

void ChatDialog::sendMessage() {
	QHostAddress address(myIPAddressEdit->text());
	quint16 port = myPortEdit->text().toUInt();
	QString message = myMessageEdit->text();
	myMessagesList->addItem("Self: " + message);
	myMessageEdit->text() = "";
	mySocket->writeDatagram(message.toUtf8(), address, port);
}

void ChatDialog::receiveMessage() {
	while (mySocket->hasPendingDatagrams()) {
		QByteArray datagram;
		datagram.resize(mySocket->pendingDatagramSize());
		QHostAddress senderAddress;
		quint16 senderPort;
		mySocket->readDatagram(datagram.data(), datagram.size(), &senderAddress, &senderPort);
		myMessagesList->addItem(senderAddress.toString() + " ( " + QString::number(senderPort) + " ): " + QString::fromUtf8(datagram));
	}
}
