#ifndef CONSOLE_H
#define CONSOLE_H

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
#include <QXmlSimpleReader>
#include <QXmlDefaultHandler>
#include <QXmlInputSource>

#include "State.h"


class Console:public QDialog{
  Q_OBJECT;
  private:
  quint16 myport;
  QHostAddress myip;
  quint16 mysendport;
  QHostAddress mysendip;

  bool mysendportset;

  QPushButton* myset;
  QPushButton* myleft;
  QPushButton* myright;
  QPushButton* mystop;
  QPushButton* mystart;

  QLineEdit* myportedit;
  QLineEdit* myipedit;

  QUdpSocket* mysocket;

  State* mystate;
  private:
  void connectButtons();
  void setWidgets();

  public:
  Console(QWidget* p, const char* ip, quint16 port);
  bool isSendPortSet();
  void parseDatagram(QByteArray datagram);

  void setstatetype(int value);
  void setballscount(int value);
  void setwindowwidth(int value);
  void setballx(int value);
  void setbally(int value);
  void setracketx(int value);
  void setrackethalfwidth(int value);
  void analizestate();
  
  public slots:
  void set();
  void sendStart();  
  void sendStop();
  void sendRight();
  void sendLeft();
  void Read();
};




#endif
