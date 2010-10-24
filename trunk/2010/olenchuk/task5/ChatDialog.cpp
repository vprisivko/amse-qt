#include "ChatDialog.h"
#include <QtGui>
#include <QUdpSocket>


ChatDialog::ChatDialog(QWidget *parent) : QDialog(parent) {

	myPort = 0;

	listWidget = new QListWidget;
	
	ipEdit = new QLineEdit;
	
	portEdit = new QLineEdit;
	portEdit->setValidator(new QIntValidator(1, 65535, this));
	lineEdit = new QLineEdit;

	sendButton = new QPushButton(tr("Send"));

	QHBoxLayout *netLayout = new QHBoxLayout; 
	netLayout->addWidget(ipEdit);
	netLayout->addWidget(portEdit);
	
	QHBoxLayout *sendLayout = new QHBoxLayout; 
	sendLayout->addWidget(lineEdit);
	sendLayout->addWidget(sendButton);

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(listWidget);
	mainLayout->addItem(netLayout);
	mainLayout->addItem(sendLayout);

	connect(sendButton,SIGNAL(clicked()),SLOT(sendMessage()));
	
	setLayout(mainLayout);
}
bool ChatDialog::initSocket(int port) {
	myPort = port;
	udpSocket = new QUdpSocket(this);
	if (udpSocket->isValid()) {
		return false;
	}

	if (!(udpSocket->bind(QHostAddress::LocalHost, port))) {
		return false;
	}
	
	setWindowTitle("Chat Name " + QString::number(port));
	
	connect(udpSocket, SIGNAL(readyRead()), this, SLOT(readMessage()));

	ipEdit->setText(QHostAddress(QHostAddress::LocalHost).toString());

	return true;
}
void ChatDialog::readMessage() {
	while (udpSocket->hasPendingDatagrams()) {
		QByteArray datagram;
		datagram.resize(udpSocket->pendingDatagramSize());
		QHostAddress sender;
		quint16 senderPort;

		udpSocket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

		QString str = QString::number(senderPort) + ": " + QString(datagram);
		listWidget->addItem(str);
	}
	
}
void ChatDialog::sendMessage() {
	QString message = lineEdit->text();
	QString copyMessage = message;
	copyMessage.replace(" ","");
	if (copyMessage.length() == 0) {
		return;
	}
	QByteArray datagram;
	datagram.append(message);

	QHostAddress destination;
	if (!destination.setAddress(ipEdit->text())) {
		QMessageBox::warning(0, "Chat", "Wrong ip address");
		return;
	}
	
	quint16 destinationPort = portEdit->text().toInt();
    	if (destinationPort == 0) {
		QMessageBox::warning(0, "Chat", "Enter to send destination");
		return;
	}

	qint64 sended = udpSocket->writeDatagram(datagram.data(), destination, destinationPort);
	if (sended == -1) {
		QMessageBox::warning(0, "Chat", "Network failure");
		return;
	}
	lineEdit->clear();
	QString str = QString::number(myPort) + ": " + message;
	listWidget->addItem(str);
}
















