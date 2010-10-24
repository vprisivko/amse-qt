#ifndef CHAT_H
#define CHAT_H

#include <QtGui/QDialog>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtNetwork/QUdpSocket>
#include <QtNetwork/QHostAddress>
#include <QtGui/QPushButton>


class Chat : public QDialog
{
  Q_OBJECT

private:

  //edits
  QLineEdit* myPortEdit;
  QLineEdit* myAddressEdit;
  QLineEdit* myNicknameEdit;
  QLineEdit* myMessageEdit;

  //controls
  QPushButton* mySendButton;

  //view
  QListWidget* myMessageList;

  //networking
  QHostAddress myAddress;
  uint myPort;
  QUdpSocket mySocket;

private:

  void setUpWidgets();
  void connectSlots();

private slots:

  void send();
  void receive();

public:

  Chat(ushort port, QWidget *parent = 0);
  ~Chat();
};

#endif // CHAT_H
