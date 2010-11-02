#include "Control.h"
#include "SaxHandler.h"
#include <QtGui>
#include <QUdpSocket>

Control :: Control(QWidget *parent) : QDialog(parent) {

	labelLives = new QLabel;
	toPortEdit = new QLineEdit;
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
	mainLayout->addWidget(toPortEdit);
	mainLayout->addWidget(labelLives);
	mainLayout->addItem(topLayout);
	setLayout(mainLayout);

	setFocusPolicy(Qt::StrongFocus);

	connect(moveLeftButton, SIGNAL(clicked()), this, SLOT(moveLeft()));
	connect(moveRightButton, SIGNAL(clicked()), this, SLOT(moveRight()));
	connect(restartButton, SIGNAL(clicked()), this, SLOT(restart()));
}
bool Control :: initSocket(int port, QString ipAddress) {
	this->port = port;
	udpSocket = new QUdpSocket(this);
	if (udpSocket->isValid()) {
		return false;
	}
	hostAddress.setAddress(ipAddress);
	if (!(udpSocket->bind(hostAddress, port))) {
		return false;
	}
	
	setWindowTitle("Port: " + QString::number(port) + " " + "ip: " + ipAddress);
	
	connect(udpSocket, SIGNAL(readyRead()), this, SLOT(awaitState()));
	
	return true;
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

	udpSocket->writeDatagram(sendText.toAscii(), hostAddress, toPortEdit->text().toInt());
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

	udpSocket->writeDatagram(sendText.toAscii(), hostAddress, toPortEdit->text().toInt());
	setFocus();
}
void Control :: stateUpdated() {
	labelLives->setText("Lives: " + QString::number(state->lives) + "Width: " + QString::number(state->width) + "Y: " + QString::number(state->y));

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














