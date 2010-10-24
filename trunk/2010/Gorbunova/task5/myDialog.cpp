#include "myDialog.h"
#include <QByteArray>
#include<QHostAddress>
#include <QHostAddress>
#include <QUdpSocket>
myDialog::myDialog(int _myport){
  myport=_myport;
  createWidgets();
  
  udpSocket = new QUdpSocket(this);
  if(!udpSocket->bind(myport)){
    printf("fail\n");
    exit(-1);
  }
  connects();
}
void myDialog::connects(){
  connect(send, SIGNAL(clicked()), this, SLOT(Send()) );
  QObject::connect(udpSocket, SIGNAL( readyRead()),this, SLOT(Read()) );
}
void myDialog::createWidgets(){
  this->setLayout( new QVBoxLayout());
  
  centralText = new QListWidget(this);
  this->layout()->addWidget(centralText);
  
  QHBoxLayout* ipconfig = new QHBoxLayout();
  ip = new QLineEdit(this);
  ipconfig->addWidget(ip);
  port = new QLineEdit(this);
  ipconfig->addWidget(port);
  this->layout()->addItem(ipconfig);
  
  QHBoxLayout* text = new QHBoxLayout();
  textEdit = new QLineEdit(this);
  text->addWidget(textEdit);
  send = new QPushButton( "Send", this);
  text->addWidget(send);
  this->layout()->addItem(text);
  
} 
void myDialog::Send(){
  QByteArray currentText;
  currentText.append(textEdit->text());
  QHostAddress exitip(ip->text());
  quint16 exitPort = port->text().toInt();
  udpSocket->writeDatagram(currentText,exitip,exitPort);
  QString outStr = "I:\t";
  outStr += currentText.data();
  centralText->addItem( outStr );
  textEdit->setText( "" );
}

void myDialog::Read(){
 while (udpSocket->hasPendingDatagrams()) {
    QByteArray datagram;
    datagram.resize( udpSocket->pendingDatagramSize() );
    QHostAddress exitHost;
    quint16 exitPort;
    udpSocket->readDatagram( datagram.data(), datagram.size(), &exitHost, &exitPort );
    centralText->addItem( exitHost.toString() + ":\t" + datagram.data()) ;
  }
}
  
