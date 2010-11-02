#ifndef MAGICBALL_H
#define MAGICBALL_H

#include <QDialog>

class QUdpSocket;
class Racket;
class Ball;
class State;
class SaxHandler;
class QLineEdit;

class MagicBall : public QDialog {

	Q_OBJECT

	public: 
		MagicBall(QWidget *parent = 0);
	
	public:
		bool initSocket(int port);
		int getSpeed();

	public:
		Racket *racket;
		Ball *ball;
	
	protected:
		void timerEvent(QTimerEvent *event);
		void paintEvent(QPaintEvent *);

	private slots:
		void awaitCommand();
		
	private:
		void sendState();

	private:
		int x;
		int y;
		int speed;
		QString ipAddress;
		QLineEdit *toPortEdit;
		SaxHandler * commandHandler;
		QUdpSocket *udpSocket;
		quint16 port;
		State *state;
		int timer;
		int toPort;
};

#endif 

