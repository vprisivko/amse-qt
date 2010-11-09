#include "MagicBall.h"
#include "Ball.h"
#include "Racket.h"
#include "State.h"
#include "SaxHandler.h"
#include <QtGui>
#include <QDomDocument>
#include <QUdpSocket>
#include <QNetworkInterface>
#include <QHostAddress>


MagicBall :: MagicBall(QWidget *parent) : QDialog(parent) {
	blink = false;
	livesLineGradation = 3;
	port = 0;
	toPort = 0;
	ipAddress = "";
	timerPaint = new QTimer(this);
	timerBlink = new QTimer(this);
	ball = new Ball();	
	racket = new Racket();
	
	racket->setWindowSize(width(), height());
	racket->setCoordinates(width()/2, height() - 30);
	ball->setWindowSize(width(), height());
	ball->setCenterX(0 + ball->getDefRad());
	ball->setCenterY(0 + ball->getDefRad());
	state = new State(this);
	commandHandler = new SaxHandler(this);
	setPort();
	setToPort();

	connect(timerPaint, SIGNAL(timeout()), this, SLOT(updateTimerPaint()));
	connect(timerBlink, SIGNAL(timeout()), this, SLOT(updateTimerBlink()));
}
void MagicBall :: startTimerPaint() {
	while (blink) {
	//wait
	}
	timerPaint->start(5);
}
void MagicBall :: timeControl() {
	timerPaint->stop();
	timerBlink->start(1000);
	QTimer :: singleShot(5000, this, SLOT(updateTimers()));
}
bool MagicBall :: initSocket() {
	udpSocket = new QUdpSocket(this);
	if (udpSocket->isValid()) {
		return false;
	}

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
	hostAddress.setAddress(ipAddress);
	if (!(udpSocket->bind(hostAddress, port))) {
		return false;
	}
	
	setWindowTitle(tr("Magic Ball Port: ") + QString::number(port) + tr(" ip: ") + ipAddress);
	
	connect(udpSocket, SIGNAL(readyRead()), this, SLOT(awaitCommand()));

	return true;
}
void MagicBall :: sendState() {
	QDomDocument stateDoc;
	stateDoc.appendChild(state->serialize(&stateDoc));
	
	QByteArray datagram;
	datagram.append(stateDoc.toString().toAscii());

	if (toPort == 0) {
		setToPort();
	}
	quint16 destinationPort = toPort;
    	if (destinationPort == 0) {
		QMessageBox::warning(0, "Magic Ball", "Enter to send destination");
		return;
	}

	qint64 sended = udpSocket->writeDatagram(datagram.data(), hostAddress, destinationPort);
	if (sended == -1) {
		QMessageBox::warning(0, "Magic Ball", "Network failure");
		return;
	}
}
void MagicBall :: setPort() {
	bool ok;
	int port = QInputDialog :: getInt(this, tr("Port"), tr("Enter Port, range 0....65535"), 10000, 0, 65535, 1, &ok);
	if (ok) {
		this->port = port;
		if (!(initSocket())) {
			QMessageBox::critical(0, "Magic Ball", "Port " + QString::number(port) + " is busy");
			setPort();
		}
	}
}
void MagicBall :: setToPort() {
	bool ok;
	int toPort = QInputDialog :: getInt(this, tr("Destination Port"), tr("Enter toPort, range 0....65535"), 10001, 0, 65535, 1, &ok);
	if (ok) {
		this->toPort = toPort;
	}
}
void MagicBall :: awaitCommand() {
	//while (udpSocket->hasPendingDatagrams()) {
		QByteArray datagram;
		datagram.resize(udpSocket->pendingDatagramSize());
		QHostAddress sender;
		quint16 senderPort;

		udpSocket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
		
		commandHandler->readDatagram(datagram);
	//}
}
void MagicBall :: updateTimerPaint() {
	state->updateState();
	update();
}
void MagicBall :: updateTimerBlink() {
	blink = blink ? false : true;
	update();
}
void MagicBall :: updateTimers() {
	timerBlink->stop();
	blink = false;
	ball->setCenterX(racket->getCoordinates().x() + racket->getRacketSize().width()/2);
	ball->setCenterY(racket->getCoordinates().y() - ball->getDefRad());
	if (state->getLives() != 0) {
		startTimerPaint();
	}
}
void MagicBall :: acceleration() {
	timerPaint->stop();
	timerPaint->start(3);
	QTimer :: singleShot(3000, this, SLOT(stopAcceleretion()));
}
void MagicBall :: stopAcceleretion() {
	timerPaint->stop();
	startTimerPaint();
}
void MagicBall :: paintEvent(QPaintEvent *) {
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);
	if (ball->getCenter().x() + ball->getDefRad() > width()) {
		ball->setCenterX(ball->getCenter().x()/(ball->getWidth()/width()));
	}
	if (ball->getCenter().y() + ball->getDefRad() > height()) {
		ball->setCenterY(ball->getCenter().y()/(ball->getHeight()/height()));
	}
	//Прилипание шарика к стенке
	if ((width() > ball->getWidth()) & (ball->getCenter().x() + ball->getDefRad() >= ball->getWidth())) {	
		ball->setCenterX(ball->getCenter().x() + (width() - ball->getWidth()));
	}	
	if ((height() > ball->getHeight()) & (ball->getCenter().y() + ball->getDefRad() >= ball->getHeight())) {
		ball->setCenterY(ball->getCenter().y() + (height() - ball->getHeight()));
	}	
	
	ball->setWindowSize(width(), height());
	racket->setWindowSize(width(), height());

	if (state->getLives() == 3) {
		painter.setBrush(Qt :: red);
	} else {
		QLinearGradient linearGradient(0, height()/100, width(), height()/100);
		linearGradient.setColorAt(0, Qt :: red);
		linearGradient.setColorAt(state->getLives()/livesLineGradation, Qt :: white);
		painter.setBrush(linearGradient);
	}
	painter.setPen(Qt :: black);
	QRectF drawLives(0, 0, width(), height()/50);
	painter.drawRoundedRect(drawLives, 0, 0, Qt :: RelativeSize);
	
	
	painter.setBrush(Qt::Dense1Pattern);
	painter.setPen(Qt::black);
	QRectF rectangle = racket->getRectangle();
	painter.drawRoundedRect(rectangle, 20, 30, Qt :: RelativeSize);

	if (blink) {
		painter.setBrush(Qt :: NoBrush);
	} else {
		QRadialGradient radialGradient(ball->getCenter().x(), ball->getCenter().y(), ball->getDefRad(), 
					ball->getCenter().x(), ball->getCenter().y() + ball->getDefRad());
		radialGradient.setColorAt(0, Qt::lightGray);
		radialGradient.setColorAt(0.1, Qt::lightGray);
		radialGradient.setColorAt(1, Qt::black);
		painter.setBrush(radialGradient);
	}
	painter.setPen(Qt::NoPen);
	painter.drawEllipse(ball->getCenter(), ball->getRadius().x(), ball->getRadius().y());
	painter.end();
	sendState();
}










