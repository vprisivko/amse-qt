#ifndef _GAME_H_
#define _GAME_H_

#include <QWidget>
#include <QDialog>
#include <QTimerEvent>
#include <QPaintEvent>
#include <QPoint>
#include <QSize>
#include <QUdpSocket>
#include <QString>
#include <QHostAddress>
#include <QTimer>
#include <QDomDocument>
#include <QDomElement>
#include <QXmlDefaultHandler>

class GameDialog : public QDialog {
    Q_OBJECT;
    
    public:
        GameDialog(quint16 port, QWidget *parent = NULL);
        
    public:
        virtual void paintEvent(QPaintEvent* e);
    
    private:
        const int defRadius;
        struct Ball {
            int initRadius;
            QSize curRadius;
            QPoint coord;
            int dx,dy;
            QDomElement serialize(QDomDocument &domDocument) const;
        } myBall;

        struct Racket {
            int x, y;
            int dx;
            int height, width;
            QDomElement serialize(QDomDocument &domDocument) const;
        } myRacket;

    private:
        bool myGameStarted;
        int myLives;

    private:
        QHostAddress myControlHostAddress;
        quint16 myControlHostPort;

        QTimer* mySendStateTimer;
        QTimer* myMovingBallTimer;

    private:
        QUdpSocket* mySocket;
        
    private:
        void initSocket(quint16 port);
        void createConnects();
        void setTimers();

    private:
        QDomDocument serialize() const;

    private:
        void startMoveBall();
        void toStartPosition();
        void lostBall();

    private:
        struct ControlCommand {
            QString cmd;
        };

        class CommandXmlHandler: public QXmlDefaultHandler {
            public:
                CommandXmlHandler(ControlCommand* cmd);
                bool startElement(const QString &, const QString &, const QString &, const QXmlAttributes &);
            private:
                ControlCommand* myCommand;
        };

        void processCommand(const ControlCommand& cmd);

    public slots:
        void receiveSlot();
        void sendStateSlot();
        void moveBallSlot();
        void moveRacketSlot();
};

#endif
