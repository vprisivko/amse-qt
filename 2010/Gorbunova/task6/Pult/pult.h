#ifndef _PULT_
#define _PULT_

#include <QDialog>
#include <QPushButton>
#include <QUdpSocket>
#include <QHostAddress>
#include <QByteArray>
#include <QWidget>
#include <QLineEdit>
#include "myParser.h"
#include "controlattributs.h"
class Pult: public QDialog{
  Q_OBJECT;
  
  public:
    Pult(QHostAddress  ip, int port,QWidget* parent = 0);
  private:
  
    int myport;
    QHostAddress myip;
    QHostAddress thereip;
    int thereport;
    QPushButton *left;
    QPushButton *right;
    QPushButton* set;
    QPushButton* start;
    QLineEdit* ip;
    QLineEdit* port;

    QUdpSocket *mySocket;
    
    int lifes;
    controlAttributs* attr;
    
    
    void createWidgets();
    void connects();
    friend class myParser;

  public slots:
    void rightButton();
    void leftButton();
    void setButton();
    void startButton();
    void readDatagram();
};
    


#endif
