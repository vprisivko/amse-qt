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
	toPort = 13013;
	ball = new Ball();	
	racket = new Racket();
	state = new State(ball, racket);
	toPortEdit = new QLineEdit;
	commandHandler = new SaxHandler(this);
	
	ball->setWindowSize(width(), height());
	racket->setWindowSize(width(), height());
	racket->setCoordinates(width()/2, height() - 30);
	
	qsrand(time(0));
	x = 0;
	y = 0;
	x = qrand() % 4;
	y = qrand() % 4;
	
	if (x > 1) {
		x = 1;
	} else {
		x = -1;
	}
	if (y < 1) {
		y = 1;
	} else {
		y = -1;
	}
	speed = 1;
	timer = startTimer(20);
	
	setWindowTitle(tr("Magic Ball"));
}
bool MagicBall :: initSocket(int port) {
	this->port = port;
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
	QHostAddress hostAddress;
	hostAddress.setAddress(ipAddress);
	if (!(udpSocket->bind(hostAddress, port))) {
		return false;
	}
	
	setWindowTitle("Port: " + QString::number(port) + " " + "ip: " + ipAddress);
	
	connect(udpSocket, SIGNAL(readyRead()), this, SLOT(awaitCommand()));
	
	return true;
}
int MagicBall :: getSpeed() {
	return speed;
}
void MagicBall :: sendState() {
	QDomDocument stateDoc;
	stateDoc.appendChild(state->serialize(&stateDoc));
	
	QByteArray datagram;
	datagram.append(stateDoc.toString().toAscii());

	QHostAddress destination;
	destination.setAddress(ipAddress);
	
	//quint16 destinationPort = toPort->text().toInt();
	quint16 destinationPort = toPort;
    	if (destinationPort == 0) {
		QMessageBox::warning(0, "Chat", "Enter to send destination");
		return;
	}

	qint64 sended = udpSocket->writeDatagram(datagram.data(), destination, destinationPort);
	if (sended == -1) {
		QMessageBox::warning(0, "Chat", "Network failure");
		return;
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
void MagicBall::timerEvent(QTimerEvent *event) {
	
	if (event->timerId() != timer) {
		return;
	}

	
	if (ball->getCenter().x() - ball->getDefRad() <= rect().x()) {
		if (ball->getRadius().x() <= ball->getDefRad()/4) {
			x = -x;
		}
		if ((ball->getRadius().x() + x) <= ball->getDefRad()) {
			ball->setRadiusX(ball->getRadius().x() + x);
		}
	}
	if (ball->getCenter().y() - ball->getDefRad() <= rect().y()) {
		if (ball->getRadius().y() <= ball->getDefRad()/4) {
			y = -y;
		}
		if ((ball->getRadius().y() + y) <= ball->getDefRad()) {
			ball->setRadiusY(ball->getRadius().y() + y);
		}
	}
	if (ball->getCenter().x() + ball->getDefRad() >= width()) {
		if (ball->getRadius().x() <= ball->getDefRad()/4) {
			x = -x;
		}
		if ((ball->getRadius().x() - x) <= ball->getDefRad()) {
			ball->setRadiusX(ball->getRadius().x() - x);
		}
	}
	
	if (ball->getCenter().y() + ball->getDefRad() >= racket->getCoordinates().y()) {
		if ((ball->getCenter().x() + ball->getDefRad() >= racket->getCoordinates().x()) & 
					(ball->getCenter().x() - ball->getDefRad() <= racket->getCoordinates().x() + racket->getRacketSize().width())) {
			if (ball->getRadius().y() <= ball->getDefRad()/4) {
				y = -y;
			}
			if ((ball->getRadius().y() - y) <= ball->getDefRad()) {
				ball->setRadiusY(ball->getRadius().y() - y);
			}
		}

		if ((ball->getCenter().x() - ball->getDefRad() <= racket->getCoordinates().x() + racket->getRacketSize().width()) & 
					(ball->getCenter().x() + ball->getDefRad() >= racket->getCoordinates().x())) {
			if (ball->getRadius().y() <= ball->getDefRad()/4) {
				y = -y;
			}
			if ((ball->getRadius().y() - y) <= ball->getDefRad()) {
				ball->setRadiusY(ball->getRadius().y() - y);
			}
		}
	}
	
	if (ball->getCenter().y() + ball->getDefRad() >= height()) {
		if (ball->getRadius().y() <= ball->getDefRad()/4) {
			y = -y;
			if (ball->getLives() > 0)
				ball->setLives(ball->getLives() - 1);
		}
		if ((ball->getRadius().y() - y) <= ball->getDefRad()) {
			ball->setRadiusY(ball->getRadius().y() - y);
		}
	}
	ball->setCenterX(ball->getCenter().x() + x);
	ball->setCenterY(ball->getCenter().y() + y);
	update();
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

	painter.setBrush(Qt::Dense1Pattern);
	painter.setPen(Qt::black);
	QRectF rectangle = racket->getRectangle();
	painter.drawRoundedRect(rectangle, 20, 30, Qt :: RelativeSize);

	painter.setPen(Qt::NoPen);

	QRadialGradient gradient(ball->getCenter().x(), ball->getCenter().y(), ball->getDefRad(), 
					ball->getCenter().x(), ball->getCenter().y() + ball->getDefRad());
	gradient.setColorAt(0, Qt::lightGray);
	gradient.setColorAt(0.1, Qt::lightGray);
	gradient.setColorAt(1, Qt::black);
	painter.setBrush(gradient);
	painter.drawEllipse(ball->getCenter(), ball->getRadius().x(), ball->getRadius().y());
	painter.end();
	sendState();
}










