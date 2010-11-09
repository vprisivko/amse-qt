#include "Control.h"
#include "SaxHandler.h"
#include <QtGui>
#include <QUdpSocket>
#include <QNetworkInterface>

Control :: Control(QWidget *parent) : QDialog(parent) {
	port = 0;
	toPort = 0;
	ipAddress = "";
	labelLives = new QLabel;
	state = new State();
	stateHandler = new SaxHandler(state);

	moveLeftButton = new QPushButton("<");
	moveRightButton = new QPushButton(">");
	restartButton = new QPushButton("Restart");
	moveLeftButton->setEnabled(false);
	moveRightButton->setEnabled(false);
	restartButton->setEnabled(true);
	
	QHBoxLayout *topLayout = new QHBoxLayout();
	topLayout->addWidget(moveLeftButton);
	topLayout->addWidget(moveRightButton);
	topLayout->addWidget(restartButton);
	
	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(labelLives);
	mainLayout->addItem(topLayout);
	setLayout(mainLayout);

	setFocusPolicy(Qt::StrongFocus);

	connect(moveLeftButton, SIGNAL(clicked()), this, SLOT(moveLeft()));
	connect(moveRightButton, SIGNAL(clicked()), this, SLOT(moveRight()));
	connect(restartButton, SIGNAL(clicked()), this, SLOT(restart()));

	setSettingsSocket();
	setToPort();
}
bool Control :: initSocket() {
	udpSocket = new QUdpSocket(this);
	if (udpSocket->isValid()) {
		return false;
	}
	if (!hostAddress.setAddress(ipAddress)) {
		QMessageBox::critical(0, "Conrol", "ip " + ipAddress + " no correct, count the number of points");
		return false;
	}
	if (!(udpSocket->bind(hostAddress, port))) {
		return false;
	}
	
	setWindowTitle(tr("Magic Ball Port: ") + QString::number(port) + tr(" ip: ") + ipAddress);
	
	connect(udpSocket, SIGNAL(readyRead()), this, SLOT(awaitState()));
	
	return true;
}
void Control :: setSettingsSocket() {
	bool ok;
	int port = QInputDialog :: getInt(this, tr("Port"), tr("Enter Port, range 0....65535"), 10001, 0, 65535, 1, &ok);
	if (ok) {
		this->port = port;
	} else {
		setSettingsSocket();
	}
	
	QString ipAddress;
	QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
	for (int i = 0; i < ipAddressesList.size(); ++i) {
		if (ipAddressesList.at(i) != QHostAddress::LocalHost && ipAddressesList.at(i).toIPv4Address()) {
			ipAddress = ipAddressesList.at(i).toString();
			break;
		}
	}
	if (ipAddress.isEmpty()) {
		ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
	}
	
	ipAddress = QInputDialog :: getText(this, tr("ip"), tr("Enter ip of Magic Ball applications"), QLineEdit::Normal, ipAddress, &ok);
	if (ok && !ipAddress.isEmpty()) {
		this->ipAddress = ipAddress;
		if (!(initSocket())) {
			QMessageBox::critical(0, "Control", "ip " + ipAddress + " something is wrong, maybe port already in use someone?");
			setSettingsSocket();
		}
	}
}
void Control :: setToPort() {
	bool ok;
	int toPort = QInputDialog :: getInt(this, tr("Destination Port"), tr("Enter toPort, range 0....65535"), 10000, 0, 65535, 1, &ok);
	if (ok) {
		this->toPort = toPort;
	}
}
void Control :: awaitState() {
	//while (udpSocket->hasPendingDatagrams()) {
		QByteArray datagram;
		datagram.resize(udpSocket->pendingDatagramSize());
		QHostAddress sender;
		quint16 senderPort;

		udpSocket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
		
		stateHandler->readDatagram(datagram);
		stateUpdated();
	//}
}
void Control :: keyPressEvent(QKeyEvent *e) {
	if ((e->key() == Qt::Key_Left) && (state->canMoveLeft())) {
		moveLeft();
	}
	if ((e->key() == Qt::Key_Right) && (state->canMoveRight())) {
		moveRight();
	}
	if ((e->key() == Qt::Key_Space) && (state->lives == 0)) {
		restart();
	}
}
void Control :: sendMoveCommand(QString command) {
	QString sendText = "<command value=\"" + command + "\" />";

	if (toPort == 0) {
		setToPort();
	}

	udpSocket->writeDatagram(sendText.toAscii(), hostAddress, toPort);
}
void Control :: moveLeft()  {
	sendMoveCommand("left");
	setFocus();
}
void Control :: moveRight() {
	sendMoveCommand("right");
	setFocus();
}
void Control :: restart() {
	QString sendText = "<restart />";

	if (toPort == 0) {
		setToPort();
	}
	
	udpSocket->writeDatagram(sendText.toAscii(), hostAddress, toPort);
	setFocus();
}
void Control :: stateUpdated() {
	labelLives->setText("Lives: " + QString::number(state->lives));

	if (state->canMoveLeft()) {
		moveLeftButton->setEnabled(true);
	} else {
		moveLeftButton->setEnabled(false);
	}


	if (state->canMoveRight()) {
		moveRightButton->setEnabled(true);
	} else {
		moveRightButton->setEnabled(false);
	}
	if (state->lives == 0) {
		restartButton->setEnabled(true);
		moveLeftButton->setEnabled(false);
		moveRightButton->setEnabled(false);
	} else {
		restartButton->setEnabled(false);
	}
}














