#include <QVBoxLayout>
#include <QHBoxLayout>
#include <iostream>

#include "Arcanoid.h"

Arcanoid::Arcanoid(QWidget *parent): QDialog(parent) {

	setWindowTitle("Arcanoid: port # 5000");

	myLostBalls = 3;
	isStarted = 0;
	isGameOver = 0;

	myIpEdt = new QLineEdit(this);
	myIpLbl = new QLabel("IP = ", this);
	myPortEdt = new QLineEdit(this);
	myPortLbl = new QLabel("Port = ", this);
	myInfoLbl = new QLabel("Input ip and port of remote controller:", this);

	mySetBtn = new QPushButton("set", this);

	myGame = new Ball(this, 30, 1, 1);
	myGame->myRacket.xTopLeft = myGame->width() / 2;
	myGame->myRacket.yTopLeft = myGame->height() - 5;

	mySocket = new QUdpSocket(this);

	setLayout(new QVBoxLayout(this));
	layout()->addWidget(myGame);
	layout()->addWidget(myInfoLbl);

	QHBoxLayout *lay = new QHBoxLayout();
	lay->addWidget(myIpLbl);
	lay->addWidget(myIpEdt);
	lay->addWidget(myPortLbl);
	lay->addWidget(myPortEdt);
	layout()->addItem(lay);

	layout()->addWidget(mySetBtn);

	QObject::connect(mySetBtn, SIGNAL(pressed()), this, SLOT(set()));
	QObject::connect(this->myGame, SIGNAL(gameover()), this, SLOT(gameover()));
	QObject::connect(mySocket, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams()));
	QObject::connect(this, SIGNAL(left()), this->myGame, SLOT(moveLeft()));
	QObject::connect(this, SIGNAL(right()), this->myGame, SLOT(moveRight()));
	QObject::connect(this, SIGNAL(start()), this->myGame, SLOT(start()));
}

void Arcanoid::set() {
	QHostAddress host(myIpEdt->text());
	myIpTo = host;

	myPortTo = myPortEdt->text().toInt();

	if (!mySocket->bind(5000)) {
		std::cerr << "Try to use another port!\n";
		isStarted = 0;
	}

	this->send();
}

void Arcanoid::send() {
	QDomDocument datagram = this->serialize();
	mySocket->writeDatagram(datagram.toString().toUtf8(), myIpTo, myPortTo);
}

void Arcanoid::gameover() {
	isGameOver = 1;
	this->send();
}

QDomDocument Arcanoid::serialize() {
	QDomDocument datagram;
	QDomElement state = datagram.createElement("state");
	state.setAttribute("is_started", isStarted);
	state.setAttribute("is_gameover", isGameOver);
	datagram.appendChild(state);
	return datagram;
}

void Arcanoid::readPendingDatagrams() {
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

void Arcanoid::processReadData(const QByteArray &data) {
	QXmlSimpleReader reader;
	Arcanoid::XmlHandler *xmlHandler = new Arcanoid::XmlHandler();

	reader.setContentHandler(xmlHandler);
	QXmlInputSource buffer;
	buffer.setData(data);
	reader.parse(&buffer);

	myDirection = xmlHandler->my_direction;
	if (myDirection == -1) {
		emit left();
	}
	if (myDirection == 1) {
		emit right();
	}
	isStarted = xmlHandler->is_started;
	if (isStarted == 1) {
		emit start();
	}

	this->send();
}

bool Arcanoid::XmlHandler::startElement(const QString&, const QString&,
						const QString &name, const QXmlAttributes &attrs) {
	if (name == "start") {
		is_started = true;
	} else {
		is_started = false;
	}
	if (name == "command") {
		my_direction = attrs.value("direction").toInt();
	}

	return true;
}

