#include "SaxHandler.h"
#include "Control.h"

SaxHandler :: SaxHandler(State *state){
	this->state = state;
}
bool SaxHandler :: readDatagram(QByteArray datagram) {
	QXmlSimpleReader simpleReader;
	simpleReader.setContentHandler(this);
	QXmlInputSource inputSource;
	inputSource.setData(datagram);
	return simpleReader.parse(inputSource);
}
bool SaxHandler :: startElement(const QString &, const QString &, const QString &name, const QXmlAttributes &attrs) {
	if (name == "Lives") {
		state->lives = attrs.value("livesleft").toInt();
	}
	if (name == "Racket") {
		state->x = attrs.value("x").toDouble();
		state->y = attrs.value("y").toDouble();
		state->racketWidth = attrs.value("racketWidth").toDouble();
	}
	if (name == "Size") {
		state->width = attrs.value("width").toDouble();
		state->height = attrs.value("height").toDouble();
	}
	return true;
}

