#ifndef VIEW_H
#define VIEW_H

#include <QString>
#include <QDialog>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QHBoxLayout>
#include <QWidget>
#include <QListView>
#include <QLabel>
#include <QLayout>
#include <QMessageBox>
#include <QByteArray>
#include <QStringListModel>
#include <QHostAddress>
#include <QUdpSocket>
#include <QTimerEvent>
#include <QPoint>
#include <QRect>
#include <QPainter>
#include <QPaintEvent>
#include <QWidget>
#include <QTimer>
#include <QColor>
#include <QFont>
#include <QTime>
#include <QDomDocument>
#include <QDomElement>
#include <QXmlSimpleReader>
#include <QXmlDefaultHandler>
#include <QXmlInputSource>

#include "Ball.h"
#include "Racket.h"
#include "BallWidget.h"


class View:public QDialog{
  Q_OBJECT;
  public:
  static const int NOTSTARTED = 0;
  static const int STARTED = 1;
  static const int GAMEOVER = 2;
  static const int timeperiod = 50;
  private:
  QTimer* mytimer; 

  quint16 myport;
  QHostAddress myip;
  quint16 mysendport;
  QHostAddress mysendip;

  int mystate;
  QPushButton* myset;

  QLineEdit* myportedit;
  QLineEdit* myipedit;

  QUdpSocket* mysocket;
  BallWidget* myballwidget;
 
  bool mysendportset;
  void setWidgets();
  public:
  View(QWidget* p, const char* ip, quint16 port);
  QDomDocument serialize();
  void loseball();
  bool isSendPortSet();
  void parseDatagram(QByteArray datagram);
  void setState(int value);

  void start();
  void stop();

  void moveRacketRight();
  void moveRacketLeft();
  
  public slots:
  void set();
  void Read();
  void send();
  void gameOver();
};

#endif
