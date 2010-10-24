#include <cstdlib>
#include <ctime>
#include <QString>
#include <QByteArray>
#include <QtNetwork/QHostAddress>
#include <QApplication>
#include <QMessageBox>
#include <QIntValidator>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include "udpchat.h"


UdpChat::UdpChat(QWidget *parent /* = 0 */, int port /* = -1 */) : QDialog(parent)
{
	if(port == -1) {
		srand((unsigned)time(0));
		port = rand() + 1;
	}
	setWindowTitle("Port: " + QString::number(port));

	configureUI();
	configureUdp(port);
}

void UdpChat::configureUI()
{
	socket_ = new QUdpSocket(this);

	QVBoxLayout *thisLay = new QVBoxLayout(this);

	messages_ = new QListWidget(this);
	thisLay->addWidget(messages_);

	QHBoxLayout *lay = new QHBoxLayout();
	ipAddress_ = new QLineEdit("127.0.0.1", this);
	ipPort_ = new QLineEdit(this);
	ipPort_->setValidator(new QIntValidator(1, (1 << 16) - 1, this));
	lay->addWidget(ipAddress_);
	lay->addWidget(ipPort_);
	thisLay->addLayout(lay);

	lay = new QHBoxLayout();
	message_ = new QLineEdit(this);
	QPushButton *send = new QPushButton("Send", this);
	lay->addWidget(message_);
	lay->addWidget(send);
	thisLay->addLayout(lay);

	connect(socket_, SIGNAL(readyRead()), SLOT(receiveMessage()));
	connect(send, SIGNAL(clicked()), SLOT(sendMessage()));
}

void UdpChat::configureUdp(int port)
{
	if(socket_->isValid())
		return;
	if(socket_->bind(QHostAddress::LocalHost, port)) {
		messages_->addItem("Chat client binded at port " + QString::number(port));
	} else {
		QMessageBox::warning(this, windowTitle(), "Cannot bind socket: absolutely unknown reason");
	}
}

void UdpChat::receiveMessage()
{
	while(socket_->hasPendingDatagrams()) {
		QHostAddress senderIP;
		quint16 senderPort;
		QByteArray data;
		data.resize(socket_->pendingDatagramSize());
		if(socket_->readDatagram(data.data(), data.size(), &senderIP, &senderPort) != -1) {
			QString message = "It (" + senderIP.toString() + ":" + QString::number(senderPort);
			message += "): " + QString(data);
			messages_->addItem(message);
		}
	}
}

void UdpChat::sendMessage()
{
	QByteArray data(message_->text().trimmed().toAscii());
	if(data.isEmpty()) {
		return;
	}
	QHostAddress destAddr;
	if(!destAddr.setAddress(ipAddress_->text())) {
		QMessageBox::warning(this, windowTitle(), "Cannot send message: IP address is invalid");
		return;
	}
	bool ok = true;
	unsigned int destPort = ipPort_->text().toInt(&ok);
	if(destPort == 0 || !ok) {
		QMessageBox::warning(this, windowTitle(), "Cannot send message: IP port is invalid");
		return;
	}
	if(socket_->writeDatagram(data, destAddr, destPort) == -1) {
		QMessageBox::warning(this, windowTitle(), "Cannot send message: absolutely unknown reason");
		return;
	}

	messages_->addItem("You: " + message_->text().trimmed());
	message_->setText("");
}
