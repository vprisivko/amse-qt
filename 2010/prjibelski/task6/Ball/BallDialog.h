#ifndef BALLDIALOG_H
#define	BALLDIALOG_H

#include <QtGui/QPushButton>
#include <QtGui/QDialog>
#include <QtGui/QPainter>
#include <QtGui/QPaintEvent>
#include <QtGui/QLabel>
#include <QtCore/QTimerEvent>
#include <QtCore/QTimer>
#include <QUdpSocket>
#include <QXmlContentHandler>

#include "state.h"

class BallDialog;

class CommandXmlHandler: public QXmlDefaultHandler {
public:
    CommandXmlHandler (BallDialog * bd)
    {
        ballDial = bd;
    }

    bool startElement(  const QString &, const QString &, const QString &name, const QXmlAttributes &attrs);

private:
    BallDialog * ballDial;
};

class BallDialog: public QDialog  {
    Q_OBJECT;
public:
    BallDialog();

    void newGame() {
        state->newGame();
        ballTimer->start(20);
    }

    State * state;

private:
    QPainter * ballPainter;
    QTimer * ballTimer;

    QUdpSocket * chatSocket;
    QByteArray recievedData;
    CommandXmlHandler * commandHandler;

    QUdpSocket * socket;
    int myPort;
    int toPort;
    QString ip;
    void loadSettings();

    void paintEvent( QPaintEvent * );
    void moveBall( double & coord, double & rad, double limit, double & speed, int & compDirection );
    void compressBall( double & coord, double & rad, double radLimit, double speed, int & compDirection );

    void sendState();
    void connectAll();
    void createSocket( int portNumber );

public slots:
    void timeEvent();
    void commandRecieved();
};

#endif	/* BALLDIALOG_H */

