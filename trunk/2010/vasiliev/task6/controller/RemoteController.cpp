#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDomDocument>
#include <QXmlInputSource>
#include <iostream>

#include "RemoteController.h"

RemoteController::RemoteController(QWidget *parent): QDialog(parent) {

	setWindowTitle("Remote controller: port # 6000");

	myLostBalls = 3;
	isStarted = 0;
	isGameOver = 0;

	myLeftBtn = new QPushButton("left", this);
	myRightBtn = new QPushButton("right", this);
	myStartBtn = new QPushButton("start", this);
	myLostBallsLbl = new QLabel(QString::number(myLostBalls), this);
	myBallsLbl = new QLabel("Remained balls = ", this);
	mySetBtn = new QPushButton("set", this);
	myInfoLbl = new QLabel("Input ip and port of arcanoid app:", this);

	myLeftBtn->setEnabled(false);
	myRightBtn->setEnabled(false);
	myStartBtn->setEnabled(false);
	mySetBtn->setEnabled(true);

	mySocket = new QUdpSocket(this);

	myIpToEdt = new QLineEdit(this);
	myIpToLbl = new QLabel("IP = ", this);
	myPortToEdt = new QLineEdit(this);
	myPortToLbl = new QLabel("Port = ", this);

	setLayout(new QVBoxLayout(this));
	layout()->addWidget(myInfoLbl);

	QHBoxLayout *lay = new QHBoxLayout();
	lay->addWidget(myIpToLbl);
	lay->addWidget(myIpToEdt);
	lay->addWidget(myPortToLbl);
	lay->addWidget(myPortToEdt);
	layout()->addItem(lay);

	layout()->addWidget(mySetBtn);

	lay = new QHBoxLayout();
	lay->addWidget(myBallsLbl);
	lay->addWidget(myLostBallsLbl);
	layout()->addItem(lay);

	lay = new QHBoxLayout();
	lay->addWidget(myLeftBtn);
	lay->addWidget(myRightBtn);
	lay->addWidget(myStartBtn);
	layout()->addItem(lay);

	QObject::connect(myLeftBtn, SIGNAL(pressed()), this, SLOT(left()));
	QObject::connect(myRightBtn, SIGNAL(pressed()), this, SLOT(right()));
	QObject::connect(myStartBtn, SIGNAL(pressed()), this, SLOT(start()));

	QObject::connect(mySetBtn, SIGNAL(pressed()), this, SLOT(set()));
	QObject::connect(mySocket, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams()));
}

void RemoteController::left() {
	QDomDocument datagram;
	QDomElement command = datagram.createElement("command");
	command.setAttribute("direction", -1);
	datagram.appendChild(command);
	mySocket->writeDatagram(datagram.toString().toUtf8(), myAddressTo, myPortTo);
}

void RemoteController::right() {
	QDomDocument datagram;
	QDomElement command = datagram.createElement("command");
	command.setAttribute("direction", 1);
	datagram.appendChild(command);
	mySocket->writeDatagram(datagram.toString().toUtf8(), myAddressTo, myPortTo);

}

void RemoteController::start() {
	QDomDocument datagram;
	QDomElement command = datagram.createElement("start");
	datagram.appendChild(command);
	mySocket->writeDatagram(datagram.toString().toUtf8(), myAddressTo, myPortTo);
}

void RemoteController::set() {
	QHostAddress host(myIpToEdt->text());
	myAddressTo = host;

	myPortTo = myPortToEdt->text().toInt();

	if (!mySocket->bind(6000)) {
		std::cerr << "Try to use another port!\n";
	}
}

void RemoteController::readPendingDatagrams() {
	while (mySocket->hasPendingDatagrams()) {
		QByteArray datagram;
		datagram.resize(mySocket->pendingDatagramSize());
		QHostAddress sender;
		quint16 senderPort;

		mySocket->readDatagram(datagram.data(), datagram.size(),
					&sender, &senderPort);

		this->processReadData(datagram);
	}
}

void RemoteController::processReadData(const QByteArray &data) {
	QXmlSimpleReader reader;
	RemoteController::XmlHandler *xmlHandler = new RemoteController::XmlHandler();

	reader.setContentHandler(xmlHandler);
	QXmlInputSource buffer;
	buffer.setData(data);
	reader.parse(&buffer);

	isStarted = xmlHandler->my_started;
	isGameOver = xmlHandler->my_gameover;

	if (isStarted == 1) {
		myLeftBtn->setEnabled(true);
		myRightBtn->setEnabled(true);
		myStartBtn->setEnabled(false);
	}
	if (isGameOver == 1) {
		myLeftBtn->setEnabled(false);
		myRightBtn->setEnabled(false);
		--myLostBalls;
		if (myLostBalls > 0) {
			myLostBallsLbl->setText(QString::number(myLostBalls));
			myStartBtn->setEnabled(true);
		} else {
			myLostBallsLbl->setText("The game is over :(");
			myStartBtn->setEnabled(false);
		}
	}
}

bool RemoteController::XmlHandler::startElement(const QString&, const QString&,
						const QString &name, const QXmlAttributes &attrs) {
	if (name == "state") {
		my_started = attrs.value("is_started").toInt();
		my_gameover = attrs.value("is_gameover").toInt();
	}

	return true;
}

