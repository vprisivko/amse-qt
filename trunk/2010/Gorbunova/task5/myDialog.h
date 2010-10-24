#ifndef _MYDIALOG_
#define _MYDIALOG_
#include <QDialog>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>
#include <QUdpSocket>
#include <QMessageBox>
class myDialog:public QDialog{
  Q_OBJECT;
public:
  myDialog( int myport1 = 7777);
  int myport;
   
private:
  void createWidgets();
  void connects();

  QListWidget* centralText;
  
  QLineEdit* ip;
  QLineEdit* port;
  QLineEdit* textEdit;
  QPushButton* send;
  
  QUdpSocket* udpSocket;
public slots:
  void Send();
  void Read();
};

#endif
