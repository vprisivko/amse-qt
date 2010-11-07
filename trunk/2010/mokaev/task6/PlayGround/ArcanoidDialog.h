#ifndef _ARCANOID_DIALOG_H_
#define _ARCANOID_DIALOG_H_

#include <QDialog>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QPaintEvent>
#include <QTimerEvent>
#include <QtNetwork/QUdpSocket>
#include <QtNetwork/QHostAddress>
#include <QByteArray>
#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>
#include <QtXml/QXmlDefaultHandler>

#include "BallAndRocket.h"

const int DIALOG_WIDTH = 500;
const int DIALOG_HEIGHT = 500;
const int BALLS_IN_RESERVE = 3;

class ArcanoidDialog : public QDialog{
	Q_OBJECT;
    public:
        ArcanoidDialog( QHostAddress& ip, int port, QWidget* parent = 0 );
    private:
        void createWidgets();
        void addWidgets();
        void createSocket();
        void setConnection();

    public slots:
        void readDatagrams();
        void setIpAndPort();
        void gameOver();

    signals:
	void left();
	void right();
	void start();

    private:
        void send();
        QDomDocument serialize();
        void parseData( const QByteArray& );

    private:

	class XmlHandler: public QXmlDefaultHandler {
            public:
		bool startElement(const QString &, const QString &, const QString & name, const QXmlAttributes & attrs);
		int my_direction;
                bool is_started;
	};

        friend class ArcanoidDialog :: XmlHandler;

    private:
        QLabel* ipLabel;
        QLabel* portLabel;
        QLabel* infoLabel;

        QLineEdit* ipTextBox;
        QLineEdit* portTextBox;

        QPushButton* connectButton;

        BallWidget* myGame;

    private:
        QUdpSocket* udpSocket;
        QHostAddress myAddress;
        QHostAddress hostAddress;

    private:
        int myPort;
        int ctrlPort;
        int ballsInReserve;
	int isStarted;
	int isGameOver;
	int myDirection;

};

#endif
