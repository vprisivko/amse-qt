#include "SaxHandler.h"
#include "MagicBall.h"
#include "Racket.h"
#include "Ball.h"
#include "State.h"


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
		magicBall->state->restartState();
	}
	if (name == "command") {
		if (attrs.value("value") == "right") {
			magicBall->racket->setCoordinateX(magicBall->racket->getCoordinates().x() + magicBall->state->getSpeed() * 20);
		}
		if (attrs.value("value") == "left") {
			magicBall->racket->setCoordinateX(magicBall->racket->getCoordinates().x() - magicBall->state->getSpeed() * 20);
		}
	}
	return true;
}

