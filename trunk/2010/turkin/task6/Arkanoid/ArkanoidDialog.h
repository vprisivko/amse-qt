#ifndef _ARKANOID_DIALOG_H_
#define _ARKANOID_DIALOG_H_

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


class ArkanoidDialog : public QDialog {
    Q_OBJECT;
    
    public:
        ArkanoidDialog(quint16 port, QWidget *parent = NULL);
        
    public:
       
        virtual void paintEvent(QPaintEvent* e);
    
    private:
        
        const int DEFAULT_RADIUS;

    private: // main game objects
        struct Ball {
            int initRadius;
            QSize curRadius;
            QPoint coord;
            int dx,dy;
            QDomElement serialize(  QDomDocument &domDocument  ) const;
        } myBall;
        struct Pad {
            int x, y;
            int dx;
            int height, width;
            QDomElement serialize(  QDomDocument &domDocument  ) const;
        } myPad;

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
        void makeStartPosition();
        void lostBall();

    private:

        struct ControlCommand {
            QString command;
        };

        class CommandXmlHandler: public QXmlDefaultHandler {
        public:
            CommandXmlHandler(ControlCommand* command);
            bool startElement(const QString &, const QString &, const QString &, const QXmlAttributes &);
        private:
            ControlCommand* myCommand;

        };

   private:
        void processCommand(const ControlCommand& command);
        
    signals:

    public slots:
        void receiveSlot();
        void sendStateSlot();
        void moveBallSlot();
        void movePadSlot();
		
          

};


#endif
