#ifndef BALLDIALOG_H
#define BALLDIALOG_H

#include <QtGui/QDialog>
#include <QPainter>
#include <QKeyEvent>
#include <QDialog>
#include <QColor>
#include <QRect>
#include <QMessageBox>
#include <QDomElement>
#include <QXmlDefaultHandler>
#include <QHostAddress>
#include <QUdpSocket>
#include <QDataStream>

#define TIMER_INTERVAL 20
#define WINDOW_WIDTH 700
#define WINDOW_HEIGHT 500
#define BALL_RADIUS 20
#define RACKET_WIDTH 100
#define RACKET_HEIGHT 10

class BallDialog : public QDialog
{
    Q_OBJECT

public:
    BallDialog(QHostAddress, qint16, QWidget *parent = 0);

private:
    QDomDocument serialize();
    void initializeAllTheStuff();
    void processTheDatagram(QByteArray);
    void sendState();

protected:
    virtual void keyPressEvent(QKeyEvent *);
    virtual void timerEvent(QTimerEvent *);
	virtual void paintEvent(QPaintEvent *);

private slots:
    void readPendingDatagrams();

private:
    struct Racket{
    	QRect racket_rect;
    };

    Racket & getRacket(){
    	return m_racket;
    }

    struct Ball{
    	QPoint m_center;
    	int m_x_radius;
    	int m_y_radius;
    	int m_radius;

    	int m_dx;
    	int m_dy;

    	void move(Racket&, bool&);
    };

    class BallDialogXmlHandler: public QXmlDefaultHandler {
     public:
    	BallDialogXmlHandler(BallDialog * ballDialog): m_ballDialog(ballDialog){}
         bool startElement(const QString &, const QString &, const QString &, const QXmlAttributes &);
     private:
         BallDialog * m_ballDialog;
     };

private:
    Racket m_racket;
    Ball m_ball;
    int m_ballQuantity;
    int m_timerId;
    bool m_active;

    /* Some stuff connected with the network */

    QHostAddress m_ipOfIncomeDatagram;
    qint16 m_portOfIncomeDatagram;

    QHostAddress m_ipTo;
    qint16 m_portTo;
    QUdpSocket * m_udpSocket;
};

#endif // BALLDIALOG_H
