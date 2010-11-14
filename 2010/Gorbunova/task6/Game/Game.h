#ifndef _GAME_
#define _GAME_

#include <QDialog>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QUdpSocket>
#include <QPushButton>
#include <QXmlReader>
#include <QHostAddress>
#include <QDomDocument>
#include "myHandler.h"
#include "Ball.h"

class Game: public QDialog {
  Q_OBJECT;

  public:
   Game(QHostAddress _ip, int _port,QWidget* parent = 0);

public slots:
   void noleft();
   void noright();
   void everything();
   void Start();
   void set();
   void gameover();
   void readDatagrams();

public: signals:
    void left();
    void right();
     void start();

private:
   Ball* myGame;
   QHostAddress thereip;
   int thereport;
   QHostAddress myip;
   int myport;

   int myLostBalls;
   int isStarted;
   int isGameOver;
   int isLeft;
   int isRight;
   int myDirection;

   QLineEdit* ip;
   QLineEdit* port;
   QPushButton* setButton;
   QUdpSocket* mySocket;

  friend class myHandler;

private:
  void createWidgets();
  void connects();
  void send();
  QDomDocument serialize();

};

#endif


