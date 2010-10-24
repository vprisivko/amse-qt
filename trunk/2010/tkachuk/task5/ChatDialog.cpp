#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QIntValidator>
#include <QMessageBox>

#include "ChatDialog.h"

ChatDialog::ChatDialog(quint16 port, QWidget *parent)
	: QDialog(parent)
{
	myListWidget = new QListWidget(this);
	myLineEditIp = new QLineEdit("127.0.0.1", this);
	myLineEditMessage = new QLineEdit(this);
	mySendButton = new QPushButton("Send", this);
	myUdpSocket = new QUdpSocket(this);
	myLineEditPort = new QLineEdit(QString::number(port), this);
	
	myLineEditPort->setValidator(new QIntValidator(0, 65535, myLineEditPort));
	myLineEditPort->setFixedWidth(90);
	
	resize(400, 400);
	setLayout(new QVBoxLayout());
	layout()->addWidget(myListWidget);

	QVBoxLayout *leftDownLayout = new QVBoxLayout;
	leftDownLayout->addWidget(myLineEditIp);
	leftDownLayout->addWidget(myLineEditMessage);

	QVBoxLayout *rightDownLayout = new QVBoxLayout;
	rightDownLayout->addWidget(myLineEditPort);
	rightDownLayout->addWidget(mySendButton);

	QHBoxLayout *downLayout = new QHBoxLayout;
	downLayout->layout()->addItem(leftDownLayout);
	downLayout->layout()->addItem(rightDownLayout);

	layout()->addItem(downLayout);

	QObject::connect(mySendButton, SIGNAL(clicked()), this, SLOT(sendMessage()));
	QObject::connect(myUdpSocket, SIGNAL(readyRead()), this, SLOT(receiveMessage()));

	setWindowTitle("Task5, listening port: " + QString::number(port));
	
	bool isSuccess = myUdpSocket->bind(port);
	if (!isSuccess) {
		throw std::exception();
	}
}

void ChatDialog::sendMessage() {
	if (!myLineEditIp->text().isEmpty() && !myLineEditPort->text().isEmpty()) {
		QHostAddress address(myLineEditIp->text());
		quint16 port = myLineEditPort->text().toInt();
		myUdpSocket->writeDatagram(myLineEditMessage->text().toUtf8(), address, port);
		myListWidget->addItem("Me: " + myLineEditMessage->text());
	} else {
		QMessageBox::warning(this, "Warning", "Fill up fields port and IP");
	}
}

void ChatDialog::receiveMessage() {
	while(myUdpSocket->hasPendingDatagrams()) {
		QByteArray datagram;
		datagram.resize(myUdpSocket->pendingDatagramSize());
		QHostAddress sender;
		quint16 senderPort;
		myUdpSocket->readDatagram(datagram.data(), datagram.size(),&sender, &senderPort);
		myListWidget->addItem(sender.toString() + ":" + QString::number(senderPort) + ": " + QString::fromUtf8(datagram.data()));
	}
}
