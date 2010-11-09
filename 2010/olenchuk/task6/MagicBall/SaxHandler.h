#ifndef SAXHANDLER_H
#define SAXHANDLER_H

#include <QXmlDefaultHandler>

class MagicBall;

class SaxHandler : public QXmlDefaultHandler {

	public:
		SaxHandler(MagicBall *magicBall);
	
	public:
		bool readDatagram(QByteArray datagram);
	
	public:
		bool startElement(const QString &, const QString &, const QString &name, const QXmlAttributes &attrs);
		bool endElemrnt(const QString &, const QString &, const QString &name);

	private:
		MagicBall *magicBall;
};

#endif
