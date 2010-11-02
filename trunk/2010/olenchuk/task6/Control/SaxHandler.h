#ifndef SAXHANDLER_H
#define SAXHANDLER_H

#include <QXmlDefaultHandler>

class State;

class SaxHandler : public QXmlDefaultHandler {

	public:
		SaxHandler(State *state);
	
	public:
		bool readDatagram(QByteArray datagram);
	
	public:
		bool startElement(const QString &, const QString &, const QString &name, const QXmlAttributes &attrs);
		bool endElemrnt(const QString &, const QString &, const QString &name);

	private:
		State *state;
};

#endif
