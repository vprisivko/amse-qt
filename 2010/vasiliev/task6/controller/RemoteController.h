#ifndef _REMOTE_CONTROLLER_H_
#define _REMOTE_CONTROLLER_H_

#include <QWidget>
#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QUdpSocket>
#include <QHostAddress>
#include <QXmlDefaultHandler>
#include <QLabel>

class RemoteController: public QDialog {

Q_OBJECT;

public:
	RemoteController(QWidget *parent = 0);

public slots:
	void left();
	void right();
	void start();
	void readPendingDatagrams();
	void set();

private:

	class XmlHandler: public QXmlDefaultHandler {
	public:
		bool startElement(const QString&, const QString&, const QString &name, const QXmlAttributes &attrs);
	
		int my_started;
		int my_gameover;
	};

	QPushButton *myLeftBtn;
	QPushButton *myRightBtn;
	QPushButton *myStartBtn;
	QLabel *myLostBallsLbl;
	QLabel *myBallsLbl;
	QLabel *myInfoLbl;

	QLineEdit *myIpToEdt;
	QLabel *myIpToLbl;
	QLineEdit *myPortToEdt;
	QLabel *myPortToLbl;

	QUdpSocket *mySocket;
	QHostAddress myAddressTo;
	int myPortTo;

	QPushButton *mySetBtn;

	int myLostBalls;
	int isStarted;
	int isGameOver;

	friend class RemoteController::XmlHandler;

private:
	void processReadData(const QByteArray &);

};

#endif // _REMOTE_CONTROLLER_H_

