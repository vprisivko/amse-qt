#ifndef MAGICBALL_H
#define MAGICBALL_H

#include <QDialog>
#include <QHostAddress>

class QUdpSocket;
class Racket;
class Ball;
class State;
class SaxHandler;
class QTimer;

class MagicBall : public QDialog {

	Q_OBJECT

	public: 
		MagicBall(QWidget *parent = 0);
	
	public:
		bool initSocket();
		int getSpeed();
		void startTimerPaint();
		void timeControl();
		void acceleration();
	
	public:
		Racket *racket;
		Ball *ball;
		State *state;
	
	protected:
		void paintEvent(QPaintEvent *);

	private slots:
		void awaitCommand();
		void updateTimerPaint();
		void updateTimerBlink();
		void updateTimers();
		void stopAcceleretion();
		
	private:
		void sendState();
		void setPort();
		void setToPort();

	private:
		int x;
		int y;
		int speed;
		QString ipAddress;
		SaxHandler * commandHandler;
		QUdpSocket *udpSocket;
		quint16 port;
		quint16 toPort;
		QHostAddress hostAddress;
		double livesLineGradation;
		QTimer *timerBlink;
		QTimer *timerPaint;
		bool blink;
};

#endif 

