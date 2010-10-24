#include "chat.h"

#include <QtGui/QHBoxLayout>
#include <QtGui/QVBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QRegExpValidator>
#include <QtGui/QIntValidator>
#include <QtCore/QRegExp>
#include <QtGui/QMessageBox>
#include <QtCore/QDateTime>

Chat::Chat(ushort port, QWidget *parent)
    : QDialog(parent)
{
  myPort = port;
  setWindowTitle(QString::number(myPort));
  setUpWidgets();
  connectSlots();
  if (!mySocket.bind(QHostAddress(QHostAddress::LocalHost), myPort))
  {
    QMessageBox::critical(this, "Critical error", "Couldn't bind the socket");
  }
}

void Chat::setUpWidgets()
{
  //create widgets
  myMessageList = new QListWidget(this);
  myMessageEdit = new QLineEdit("enter your message here", this);
  myAddressEdit = new QLineEdit(QHostAddress(QHostAddress::LocalHost).toString(), this);
  myPortEdit = new QLineEdit(QString::number(myPort), this);
  myNicknameEdit = new QLineEdit(this);
  mySendButton = new QPushButton("send", this);

  //set up validators for edits
  QRegExpValidator* ipValidator = new QRegExpValidator(QRegExp("[0-9]{1,3}(.[0-9]{1,3}){3,3}"), this);
  myAddressEdit->setValidator(ipValidator);
  myPortEdit->setValidator(new QIntValidator(this));

  //create layout
  QVBoxLayout* mainLayout = new QVBoxLayout;
  mainLayout->addWidget(myMessageList);

  QHBoxLayout* nicknameLayout = new QHBoxLayout;
  nicknameLayout->addWidget(new QLabel("nickname", this));
  nicknameLayout->addWidget(myNicknameEdit);
  mainLayout->addItem(nicknameLayout);

  QHBoxLayout* addressLayout = new QHBoxLayout;
  addressLayout->addWidget(myAddressEdit);
  addressLayout->addWidget(myPortEdit);
  mainLayout->addItem(addressLayout);

  QHBoxLayout* messageLayout = new QHBoxLayout;
  messageLayout->addWidget(myMessageEdit);
  messageLayout->addWidget(mySendButton);
  mainLayout->addItem(messageLayout);

  setLayout(mainLayout);
}

void Chat::connectSlots()
{
  connect(mySendButton, SIGNAL(clicked()), this, SLOT(send()));
  connect(&mySocket, SIGNAL(readyRead()), this, SLOT(receive()));
}

void Chat::send()
{
  QHostAddress destinationAddress;
  if (!destinationAddress.setAddress(myAddressEdit->text()))
  {
    QMessageBox::warning(this, "Error", "Invalid ip address");
    return;
  }
  ushort destinationPort;
  bool success = false;
  destinationPort = myPortEdit->text().toUShort(&success);
  if (!success)
  {
    QMessageBox::warning(this, "Error", "Invalid port");
    return;
  }
  QByteArray message;
  message = (QDateTime::currentDateTime().toString() + " : " + myNicknameEdit->text() +  " : " + myMessageEdit->text()).toAscii();
  mySocket.writeDatagram(message, destinationAddress, destinationPort);
}

void Chat::receive()
{
  while (mySocket.hasPendingDatagrams()) {
       QByteArray datagram;

       datagram.resize(mySocket.pendingDatagramSize());
       mySocket.readDatagram(datagram.data(), datagram.size());
       myMessageList->addItem(datagram);
   }
}


Chat::~Chat()
{

}
