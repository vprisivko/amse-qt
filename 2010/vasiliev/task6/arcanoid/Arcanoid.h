#ifndef _ARCANOID_H_
#define _ARCANOID_H_

#include <QDialog>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QUdpSocket>
#include <QPushButton>
#include <QXmlReader>
#include <QHostAddress>
#include <QDomDocument>

#include "BouncedBall.h"

class Arcanoid: public QDialog {

Q_OBJECT;

public:
	Arcanoid(QWidget *parent = 0);

public slots:
	void set();
	void gameover();
	void readPendingDatagrams();

public: signals:
	void left();
	void right();
	void start();

private:

	class XmlHandler: public QXmlDefaultHandler {
	public:
		bool startElement(const QString &, const QString &, const QString & name, const QXmlAttributes & attrs);
		int my_direction;
		int is_started;
	};

	Ball *myGame;

	QHostAddress myIpTo;
	int myPortTo;

	int myLostBalls;
	int isStarted;
	int isGameOver;
	int myDirection;

	QLineEdit *myIpEdt;
	QLabel *myIpLbl;
	QLineEdit *myPortEdt;
	QLabel *myPortLbl;
	QPushButton *mySetBtn;
	QLabel *myInfoLbl;

	QUdpSocket *mySocket;

	friend class Arcanoid::XmlHandler;

private:
	void send();
	void processReadData(const QByteArray &);
	QDomDocument serialize();

};

#endif // _ARCANOID_H_
