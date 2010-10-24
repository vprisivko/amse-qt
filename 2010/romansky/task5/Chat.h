#ifndef CHAT_H
#define CHAT_H

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

class Chat:public QDialog{
  Q_OBJECT;
  private:
  QLineEdit* mytext;
  QLineEdit* myportedit;
  QLineEdit* myipedit;
  QPushButton* mysendbutton;
  QPushButton* mysetbutton;
  quint16 myport;
  QHostAddress myip;
  quint16 mysendport;
  QHostAddress mysendip;
  QListView* mylistview;
  QUdpSocket* mysocket;
  QStringListModel* mymodel;
  bool myportset;
  bool mysendportset;
  QString mydefaultaddress;

  public:
  Chat(QWidget* parent,int port);
  bool isportset();
  bool issendportset();
  public slots:
  void Set();
  void Send();
  void Read();
};

#endif
