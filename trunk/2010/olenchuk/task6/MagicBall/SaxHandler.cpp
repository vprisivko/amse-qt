#include "SaxHandler.h"
#include "MagicBall.h"
#include "Racket.h"
#include "Ball.h"


SaxHandler :: SaxHandler(MagicBall *magicBall){
	this->magicBall = magicBall;
}
bool SaxHandler :: readDatagram(QByteArray datagram) {
	QXmlSimpleReader simpleReader;
	simpleReader.setContentHandler(this);
	QXmlInputSource inputSource;
	inputSource.setData(datagram);
	return simpleReader.parse(inputSource);
}
bool SaxHandler :: startElement(const QString &, const QString &, const QString &name, const QXmlAttributes &attrs) {
	if (name == "restart") {
		magicBall->ball->setLives(3);
	}
	if (name == "command") {
		if (attrs.value("value") == "right") {
			magicBall->racket->setCoordinateX(magicBall->racket->getCoordinates().x() + magicBall->getSpeed() * 10);
		}
		if (attrs.value("value") == "left") {
			magicBall->racket->setCoordinateX(magicBall->racket->getCoordinates().x() - magicBall->getSpeed() * 10);
		}
	}
	return true;
}

