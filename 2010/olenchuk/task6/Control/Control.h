#ifndef H_CONTROL
#define H_CONTROL

#include <QDialog>
#include <QHostAddress>

class QLabel;
class QPushButton;
class SaxHandler;
class QHostAddress;
class QUdpSocket;

struct State {
	bool canMoveRight() {
		return (x + racketWidth) < width; 
	}
	bool canMoveLeft() {
		return x > 0; 
	}
	
	int lives;
	qreal x;
	qreal y;
	qreal racketWidth;
	qreal width;
	qreal height;
};

class Control : public QDialog {
	Q_OBJECT;
    
	public:
		Control(QWidget *parent = 0);

	public:
		bool initSocket();

	public:
		State *state;
		
	protected:
		void keyPressEvent(QKeyEvent *e);
		
	private slots:
		void awaitState();
		void moveLeft();
		void moveRight();
		void restart();
		
	private:
		void sendMoveCommand(QString command);
		void stateUpdated();
		void setSettingsSocket();
		void setToPort();

	private:
		SaxHandler *stateHandler;
		quint16 port;
		quint16 toPort;
		QString ipAddress;
		QHostAddress hostAddress;
		QUdpSocket *udpSocket;
		QString str;
		QLabel *labelLives;
		QPushButton *moveLeftButton;
		QPushButton *moveRightButton;
		QPushButton *restartButton;
};

#endif
